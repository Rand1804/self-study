# codex-responses-api-proxy

> 原文：`AI/codex/codex-rs/responses-api-proxy/README.md`

## 简版

```bash
# 启动 proxy，把请求/响应对 dump 到 /tmp/proxy
cd path/to/codex/codex-rs
cargo build
echo $OPENAI_API_KEY | ./target/debug/codex-responses-api-proxy \
    --port 60001 \
    --dump-dir /tmp/proxy
```

添加到 `~/.codex/config.toml`：

```toml
[model_providers.codex-responses-api-proxy]
name = 'codex-responses-api-proxy'
base_url = 'http://127.0.0.1:60001/v1'
wire_api = 'responses'

[profiles.proxy]
model_provider = "codex-responses-api-proxy"
```

使用：

```bash
codex -p proxy
```

## 详细说明

这是一个严格 HTTP proxy，只把 `POST /v1/responses` 转发到 OpenAI API（`https://api.openai.com`），并注入 `Authorization: Bearer $OPENAI_API_KEY` header。其他所有请求都会被拒绝，返回 `403 Forbidden`。

## 预期用法

`codex-responses-api-proxy` 设计为由有权限访问 `OPENAI_API_KEY` 的 privileged user 运行，避免 unprivileged user 检查或篡改进程。

privileged user 启动：

```shell
printenv OPENAI_API_KEY | env -u OPENAI_API_KEY codex-responses-api-proxy --http-shutdown --server-info /tmp/server-info.json
```

unprivileged user 使用：

```shell
PROXY_PORT=$(jq .port /tmp/server-info.json)
PROXY_BASE_URL="http://127.0.0.1:${PROXY_PORT}"
codex exec -c "model_providers.openai-proxy={ name = 'OpenAI Proxy', base_url = '${PROXY_BASE_URL}/v1', wire_api='responses' }" \
    -c model_provider="openai-proxy" \
    'Your prompt here'
```

完成后可通过 HTTP shutdown：

```shell
curl --fail --silent --show-error "${PROXY_BASE_URL}/shutdown"
```

## 行为

- 从 `stdin` 读取 API key；调用者应通过 pipe 提供 key。
- 构造 `Bearer <key>` header，并尝试对保存该 header 的内存执行 `mlock(2)`，避免被 swap 到磁盘。
- 监听指定 port；未指定时使用 ephemeral port。
- 只接受无 query string 的 `POST /v1/responses`。
- 转发请求到 `https://api.openai.com/v1/responses`，设置 Authorization header，覆盖 Host 为 `api.openai.com`。
- 其他请求返回 `403`。
- 可写入 server info JSON：`{ "port": <u16>, "pid": <u32> }`。
- 可把 request/response JSON dump 到目录；Authorization 和 cookie 类 header 会被 redact。
- `--http-shutdown` 启用 `GET /shutdown`，让进程以 0 退出。

## CLI

```text
codex-responses-api-proxy [--port <PORT>] [--server-info <FILE>] [--http-shutdown] [--upstream-url <URL>] [--dump-dir <DIR>]
```

参数：

- `--port <PORT>`：绑定到 `127.0.0.1` 的端口；省略则选择 ephemeral port。
- `--server-info <FILE>`：监听后写入 `{ "port": <PORT>, "pid": <PID> }`。
- `--http-shutdown`：启用 `GET /shutdown`。
- `--upstream-url <URL>`：转发目标，默认 `https://api.openai.com/v1/responses`。
- `--dump-dir <DIR>`：每个 accepted proxy call 写一个 request JSON 和一个 response JSON。

Azure 示例：

```shell
printenv AZURE_OPENAI_API_KEY | env -u AZURE_OPENAI_API_KEY codex-responses-api-proxy \
  --http-shutdown \
  --server-info /tmp/server-info.json \
  --upstream-url "https://YOUR_PROJECT_NAME.openai.azure.com/openai/deployments/YOUR_DEPLOYMENT/responses?api-version=2025-04-01-preview"
```

## Notes

- 只允许 `POST /v1/responses`。
- 不允许 query strings。
- 原始 request headers 会转发给 upstream，但会覆盖 Authorization 和 Host。
- response status 和 content-type 会从 upstream 镜像。

## Hardening

实现会尽力限制 `OPENAI_API_KEY` 泄漏：从 stdin 读取，清理 stack buffer，固定 header 字符串生命周期，在 UNIX 上 `mlock` heap memory，并把 HeaderValue 标记为 sensitive。
