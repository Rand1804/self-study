# codex-network-proxy

> 原文：`AI/codex/codex-rs/network-proxy/README.md`

`codex-network-proxy` 是 Codex 的本地网络策略执行代理。它运行：

- HTTP proxy，默认 `127.0.0.1:3128`
- SOCKS5 proxy，默认 `127.0.0.1:8081`，默认启用

它执行 allow/deny policy，并支持用于只读网络访问的 `limited` 模式。

## 快速开始

### 1. 配置

`codex-network-proxy` 从 Codex 合并后的 `config.toml` 读取配置。

网络设置位于所选 permissions profile 下：

```toml
default_permissions = "workspace"

[permissions.workspace.network]
enabled = true
proxy_url = "http://127.0.0.1:3128"
enable_socks5 = true
socks_url = "http://127.0.0.1:8081"
enable_socks5_udp = true
allow_upstream_proxy = true
dangerously_allow_non_loopback_proxy = false
mode = "full" # 未设置时默认 full；limited 用于只读模式
allow_local_binding = false
dangerously_allow_all_unix_sockets = false

[permissions.workspace.network.domains]
"*.openai.com" = "allow"
"localhost" = "allow"
"127.0.0.1" = "allow"
"::1" = "allow"
"evil.example" = "deny"
```

说明：

- `enabled = false` 时 proxy 不绑定 listener。
- `allow_upstream_proxy = true` 时尊重 HTTP(S)_PROXY/ALL_PROXY upstream proxy。
- 非 loopback bind 默认会被限制为 loopback；若要暴露到 localhost 以外，必须显式 opt in。
- `mode = "limited"` 或配置 MITM hooks 时会自动启用 HTTPS MITM。
- 若 `allow_local_binding = false`，local/private networking 会被拒绝，必须显式 allowlist local IP literal 或 `localhost`。
- domain allowlist 支持 exact host 和 scoped wildcard，如 `*.openai.com` 或 `**.openai.com`；拒绝全局 `*` wildcard。

MITM hook 示例：

```toml
[permissions.workspace.network.mitm.hooks.github_write]
host = "api.github.com"
methods = ["POST", "PUT"]
path_prefixes = ["/repos/openai/"]
action = ["strip_auth"]

[permissions.workspace.network.mitm.actions.strip_auth]
strip_request_headers = ["authorization"]
```

### 2. 运行 proxy

```bash
cargo run -p codex-network-proxy --
```

### 3. 让 client 使用 proxy

HTTP(S)：

```bash
export HTTP_PROXY="http://127.0.0.1:3128"
export HTTPS_PROXY="http://127.0.0.1:3128"
export WS_PROXY="http://127.0.0.1:3128"
export WSS_PROXY="http://127.0.0.1:3128"
```

SOCKS5：

```bash
export ALL_PROXY="socks5h://127.0.0.1:8081"
```

### 4. 理解 block / debug

请求被阻止时，proxy 返回 `403` 并包含 `x-proxy-error`：

- `blocked-by-allowlist`
- `blocked-by-denylist`
- `blocked-by-method-policy`
- `blocked-by-policy`

`limited` 模式只允许 `GET`、`HEAD` 和 `OPTIONS`。HTTPS `CONNECT` 需要 MITM 才能执行 limited-mode method policy；否则会被阻止。SOCKS5 在 limited 模式下仍被阻止。

Websocket 客户端通常通过 HTTPS `CONNECT` tunnel `wss://`，这些 CONNECT targets 仍走同样 host allowlist/denylist 检查。

## Library API

`codex-network-proxy` 可作为库嵌入，提供薄 API。proxy 还暴露 policy hook，可基于 command 和 exec_policy_hint 将执行审批映射为网络访问。

启用 unix socket proxying 时，proxy bind override 仍被限制到 loopback，避免把 proxy 变成访问本地 daemon 的远程桥。
