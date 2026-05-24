# FAQ

> 原文：`AI/codex/sdk/python/docs/faq.md`

## Thread vs turn

Thread 是可持续的会话上下文；turn 是 thread 中的一次用户输入和 agent 处理周期。

## `run()` vs `stream()`

`run()` 等待 turn 完成并返回结果；streaming API 允许你逐步接收中间事件。

## Sync vs async clients

同步 client 适合脚本和简单应用；async client 适合 asyncio 服务或需要并发处理的应用。

## 如何登录？

- API key：用 `login_api_key(...)`。
- ChatGPT 交互式登录：用 `login_chatgpt()`。
- Device-code：用 `login_chatgpt_device_code()`。

## Public kwargs 是 snake_case

Python API 使用 snake_case kwargs；序列化到 app-server wire format 时会转换为 camelCase。

## 为什么只有 `thread_start(...)` 和 `thread_resume(...)`？

SDK 刻意提供较小的默认 surface，优先覆盖真实脚本和应用最常见路径。

## 为什么 constructor 失败？

`Codex()` 是 eager 的，会启动 runtime 并 initialize。如果 binary、认证、环境或 app-server 启动失败，constructor 就会失败。

## 为什么 turn “hang”？

通常需要检查 app-server 是否仍在运行、事件流是否被消费、是否有等待 approval 的请求，或是否遇到 transient overload。

## 如何安全重试？

对 transient overload 使用 `retry_on_overload`。避免盲目重试带副作用的 turn。

## 常见坑

- 忘记用 context manager 导致进程未关闭。
- 混淆 thread 和 turn。
- 在需要 streaming/interrupt 时仍使用简单 `run()`。
- Python kwargs 用 camelCase 而不是 snake_case。
