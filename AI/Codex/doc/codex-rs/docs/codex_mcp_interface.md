# Codex MCP Server Interface（实验性）

> 原文：`AI/codex/codex-rs/docs/codex_mcp_interface.md`

本文档描述 Codex 的实验性 MCP server interface：一个运行在 Model Context Protocol（MCP）transport 上的 JSON-RPC API，用于控制本地 Codex engine。

- 状态：实验性，可能随时变更。
- Server binary：`codex mcp-server` 或 `codex-mcp-server`。
- Transport：标准 MCP over stdio（JSON-RPC 2.0，line-delimited）。

## 概览

Codex 暴露 MCP-compatible methods，用于管理 threads、turns、accounts、config 和 approvals。类型位于 `app-server-protocol/src/protocol/{common,v1,v2}.rs`，server 实现位于 `app-server/`。

主要 v2 RPC：

- `thread/start`、`thread/resume`、`thread/fork`、`thread/read`、`thread/list`
- `turn/start`、`turn/steer`、`turn/interrupt`
- `account/read`、`account/login/start`、`account/login/cancel`、`account/logout`、`account/rateLimits/read`
- `config/read`、`config/value/write`、`config/batchWrite`
- `model/list`、`app/list`、`collaborationMode/list`

保留的 v1 compatibility RPC：

- `getConversationSummary`
- `getAuthStatus`
- `gitDiffToRemote`
- `fuzzyFileSearch` 及其 session start/update/stop 方法

通知：

- v2 typed notifications，如 `thread/started`、`turn/completed`、`account/login/completed`
- `codex/event/*` live agent event stream notifications
- `fuzzyFileSearch/sessionUpdated`、`fuzzyFileSearch/sessionCompleted`

审批（server -> client requests）：

- `applyPatchApproval`
- `execCommandApproval`

完整类型定义和精确形状请看 `app-server-protocol/src/protocol/{common,v1,v2}.rs`。

## 启动 server

```bash
codex mcp-server | your_mcp_client
```

也可以使用 inspector：

```bash
npx @modelcontextprotocol/inspector codex mcp-server
```

使用单独的 `codex mcp` 子命令管理 `config.toml` 中配置的 MCP server launchers。

## Threads 和 turns

新集成应使用 v2 thread 和 turn APIs：

- `thread/start` 创建 thread。
- `turn/start` 提交用户输入。
- `turn/interrupt` 停止正在运行的 turn。
- `thread/list` / `thread/read` 暴露持久化历史。

`getConversationSummary` 仍作为兼容 helper，用于通过 `conversationId` 或 `rolloutPath` 查询 summary。优先使用 `conversationId`；`rolloutPath` 查询不适用于非本地 thread stores。

## Models

用 `model/list` 获取当前 Codex build 可用模型目录。请求接受可选分页参数：

- `limit`：返回模型数。
- `cursor`：上一响应的 `nextCursor`。

每个模型包含：`id`、`model`、`displayName`、`description`、`supportedReasoningEfforts`、`defaultReasoningEffort`、`inputModalities`、`supportsPersonality`、`isDefault`、`upgrade`、`upgradeInfo`。

## Collaboration modes（实验性）

使用 `collaborationMode/list` 获取内置 collaboration mode presets。该端点不分页，一次返回完整列表。

对于 tri-state 字段（如 `reasoning_effort`、`developer_instructions`）：省略表示保留当前值，设为 `null` 表示清除，设为具体值表示更新。

发送 `turn/start` 且带 `collaborationMode` 时，`settings.developer_instructions: null` 表示使用所选模式的内置指令。

## Event stream

对话运行期间，server 会发送通知：

- `codex/event`：序列化后的 Codex event payload。
- `fuzzyFileSearch/sessionUpdated` 和 `fuzzyFileSearch/sessionCompleted`：legacy fuzzy search flow。

客户端应渲染事件，并在出现 approval request 时展示给用户。

## Tool responses

`codex` 和 `codex-reply` tools 返回标准 MCP `CallToolResult` payload。为了兼容偏好 `structuredContent` 的 MCP clients，Codex 会在 `structuredContent` 中镜像 content blocks，并附带 `threadId`。

## Approvals（server -> client）

需要批准应用变更或运行命令时，server 会向 client 发 JSON-RPC request：

- `applyPatchApproval { conversationId, callId, fileChanges, reason?, grantRoot? }`
- `execCommandApproval { conversationId, callId, approvalId?, command, cwd, reason? }`

client 必须对每个 request 回复：

```json
{ "decision": "allow" }
```

或：

```json
{ "decision": "deny" }
```

## Auth helpers

完整请求/响应形状和流程示例见 app-server README 的 Auth endpoints v2 部分。

## Legacy compatibility methods

server 仍接受少量 v1 compatibility surface：

- `getConversationSummary`
- `getAuthStatus`
- `gitDiffToRemote`
- `fuzzyFileSearch` 及其 session methods

## 兼容性与稳定性

该 interface 是实验性的。方法名、字段和事件形状可能演进。权威 schema 请看 `app-server-protocol/src/protocol/{common,v1,v2}.rs` 和 `app-server/` 中对应 server wiring。
