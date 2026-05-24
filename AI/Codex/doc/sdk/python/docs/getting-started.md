# Getting Started

> 原文：`AI/codex/sdk/python/docs/getting-started.md`

## 1. 安装

进入 `sdk/python` 并同步环境：

```bash
cd sdk/python
uv sync
source .venv/bin/activate
```

## 2. 需要时认证

如果当前 app-server session 尚未认证，先调用登录 helper。API key 登录适合脚本；ChatGPT 或 device-code 登录适合交互式应用。

## 3. 第一个 turn（同步）

```python
from openai_codex import Codex

with Codex() as codex:
    thread = codex.thread_start(model="gpt-5")
    result = thread.run("Say hello in one sentence.")
    print(result.final_response)
```

## 4. 继续同一个 thread

对同一个 `thread` 重复调用 `run(...)` 可继续上下文。

## 5. Async parity

SDK 提供同步和异步 API。异步版本与同步版本语义对应，适合 async 应用或服务。

## 6. 恢复已有 thread

如果保存了 thread id，可恢复已有 thread 并继续运行。

## 7. 公开 app-server types

公开 app-server value 和 event types 位于 `openai_codex.types`。

## 8. 下一步

- API reference：`api-reference.md`
- FAQ：`faq.md`
- Examples：`examples/README.md`
