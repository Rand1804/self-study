# Protocol v1

> 原文：`AI/codex/codex-rs/docs/protocol_v1.md`

该文档描述早期 app/server 或 client 协议中的 v1 entities、interface、transport 和示例流程。v1 现在主要用于兼容；新开发应优先看 v2 app-server protocol。

## Entities

协议围绕会话、用户输入、agent 输出、事件和状态更新建模。

## Interface

Interface 定义 client 如何提交输入、接收事件、处理中断和恢复状态。

## UserInput items

用户输入可以包含文本、附件、文件引用或其他结构化输入。具体 shape 以协议类型定义为准。

## Transport

Transport 负责在 client 与 server 间传输请求、响应和通知。

## Example flows

典型流程包括：

- 基础 UI flow：创建会话、发送输入、渲染 agent 事件。
- Task interrupt：在任务运行中发送 interrupt，并处理后续状态。

## 备注

该协议文档保留用于历史兼容。实际新集成应优先参考 `codex-rs/app-server/README.md` 和 v2 protocol definitions。
