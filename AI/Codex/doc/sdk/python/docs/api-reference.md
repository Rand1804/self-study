# OpenAI Codex SDK — API Reference

> 原文：`AI/codex/sdk/python/docs/api-reference.md`

## Package Entry

包根导出常用 client、登录 helper、错误类型、retry helper 和公开 types。

## Codex（同步）

`Codex()` 是同步 client，构造时会启动 app-server 并完成 initialize。推荐使用 context manager：

```python
with Codex() as codex:
    ...
```

常用方法：

- `thread_start(...)`
- `thread_resume(...)`
- `login_api_key(...)`
- `login_chatgpt(...)`
- `login_chatgpt_device_code(...)`
- `logout()`
- `account()`

## AsyncCodex

`AsyncCodex` 提供与同步 API 对应的 async parity，适合 asyncio 应用。

## Login handles

### ChatgptLoginHandle / AsyncChatgptLoginHandle

表示正在进行的 ChatGPT 登录流程。通常读取 `auth_url`，让用户打开，然后 `wait()` 等待完成。

### DeviceCodeLoginHandle / AsyncDeviceCodeLoginHandle

表示 device-code 登录流程。适合无法直接打开浏览器的环境。

## Thread / AsyncThread

`Thread` 表示一个 Codex 会话线程。常用方法：

- `run("...")`：启动并等待 turn 完成。
- `turn(...)`：创建 turn handle，用于 streaming、steering 或 interrupt。

## TurnHandle / AsyncTurnHandle

用于控制单个 turn：

- 运行 turn。
- 流式消费事件。
- 需要时 steer 或 interrupt。

## Inputs

Plain string 可作为文本输入简写。更复杂输入可使用公开 input types。

## Public Types

公开类型位于 `openai_codex.types`，对应 app-server v2 wire models。

## Retry + errors

对于 transient overload，可使用 `retry_on_overload`。错误类型区分启动、协议、认证、运行时等失败。

## Example

常见模式：创建 `Codex` client，启动 thread，运行 prompt，读取 `final_response` 和 items。
