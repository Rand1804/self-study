# OpenAI Codex Python SDK（实验性）

> 原文：`AI/codex/sdk/python/README.md`

这是实验性 Python SDK，用于通过 stdio 上的 `codex app-server` JSON-RPC v2 控制 Codex。它提供一个小而实用的默认 API surface，适合真实脚本和应用。

生成的 wire-model 层来自 pinned `openai-codex-cli-bin` runtime package，并作为 Pydantic models 暴露。Python 字段使用 snake_case，序列化回 app-server 时使用 camelCase wire format。

包根导出 ergonomic client API；公开 app-server value 和 event types 位于 `openai_codex.types`。

## 安装

```bash
cd sdk/python
uv sync
source .venv/bin/activate
```

发布版 SDK 会 pin 精确版本的 `openai-codex-cli-bin` runtime dependency，版本与 SDK 相同。仅当你明确要使用特定本地 app-server binary 时，才传 `AppServerConfig(codex_bin=...)`。

## 快速开始

```python
from openai_codex import Codex

with Codex() as codex:
    # 如果该 app-server session 尚未认证，先调用 login_api_key(...)
    thread = codex.thread_start(model="gpt-5")
    result = thread.run("Say hello in one sentence.")
    print(result.final_response)
    print(len(result.items))
```

`thread.run(...)` 和 `thread.turn(...).run()` 返回 `TurnResult`。如果 turn 完成但没有 final-answer 或 phase-less assistant message item，`final_response` 为 `None`。

## 登录

按应用选择 auth helper：

```python
from openai_codex import Codex

with Codex() as codex:
    codex.login_api_key("sk-...")
    account = codex.account()
    print(account.account)
```

交互式 ChatGPT 登录返回 handle。打开提供的 URL 或 device-code 页面，然后等待 completion event：

```python
with Codex() as codex:
    login = codex.login_chatgpt()
    print(login.auth_url)
    completed = login.wait()
    print(completed.success)
```

可用 `login_chatgpt_device_code()` 做 device-code auth，用 `handle.cancel()` 停止进行中的交互登录，用 `logout()` 清除当前 app-server account session。

## 文档地图

- Golden path tutorial：`docs/getting-started.md`
- API reference：`docs/api-reference.md`
- Common decisions and pitfalls：`docs/faq.md`
- Runnable examples index：`examples/README.md`
- Jupyter walkthrough：`notebooks/sdk_walkthrough.ipynb`

## 示例

```bash
cd sdk/python
python examples/01_quickstart_constructor/sync.py
python examples/01_quickstart_constructor/async.py
```

## Runtime

发布版 SDK 会 pin 精确版本的 `openai-codex-cli-bin` package，该 runtime package 携带目标 wheel 平台对应的 binary。SDK package 版本必须与 runtime package 版本匹配。

## 兼容性和版本

- Package：`openai-codex`
- Runtime package：`openai-codex-cli-bin`
- Python：`>=3.10`
- Target protocol：Codex `app-server` JSON-RPC v2
- Versioning rule：SDK package 版本即底层 Codex runtime 版本。

## Notes

- `Codex()` 是 eager 的，会在 constructor 中执行 startup + `initialize`。
- 使用 context managers（`with Codex() as codex:`）确保 shutdown。
- 任何接受 turn input 的地方都接受 plain string，它是 `TextInput(...)` 的简写。
- 常见场景优先使用 `thread.run("...")`。
- 需要 streaming、steering 或 interrupt control 时使用 `thread.turn(...)`。
- 对 transient overload，可使用包根导出的 `retry_on_overload`。
