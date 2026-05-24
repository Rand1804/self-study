# codex-app-server

> 原文：`AI/codex/codex-rs/app-server/README.md`

`codex-app-server` 是 Codex 的应用服务器协议实现，用于通过 JSON-RPC 管理 threads、turns、accounts、config、models、apps、goals、compaction、auth 和事件流。原文是完整 API 参考，包含大量请求/响应示例；本译文保留其结构和主要接口语义，作为中文查阅入口。

## 协议

App server 使用 JSON-RPC 风格协议。新开发应优先使用 v2 协议；v1 主要用于兼容旧客户端。

核心概念：

- **Thread**：一个可持久化、可恢复的 Codex 会话线程。
- **Turn**：用户向 thread 提交的一次输入，以及 agent 处理该输入产生的事件和结果。
- **Notification**：server 主动发给 client 的状态、事件或流式更新。
- **Approval**：server 向 client 请求授权，例如执行命令或应用 patch。

## 生命周期概览

典型流程：

1. client 初始化连接。
2. 登录或读取账号状态。
3. 创建或恢复 thread。
4. 启动 turn。
5. 监听事件流。
6. 必要时处理 approvals。
7. 读取 thread、turn 或 metadata。
8. 归档、压缩或恢复 thread。

## API 概览

常见 v2 RPC：

| 资源 | 方法 |
| --- | --- |
| Thread | `thread/start`、`thread/resume`、`thread/fork`、`thread/read`、`thread/list` |
| Turn | `turn/start`、`turn/steer`、`turn/interrupt` |
| Account | `account/read`、`account/login/start`、`account/login/cancel`、`account/logout`、`account/rateLimits/read` |
| Config | `config/read`、`config/value/write`、`config/batchWrite` |
| Model | `model/list` |
| App | `app/list` |
| Collaboration Mode | `collaborationMode/list` |
| Goal | 设置、更新、读取 thread goal |
| Thread metadata | 更新 stored thread metadata |
| Thread lifecycle | archive、unarchive、compact |

## Thread 示例

启动或恢复 thread 的核心语义：

- `thread/start` 创建新 thread，并可附带工作目录、模型、配置或初始输入。
- `thread/resume` 恢复已有 thread。
- `thread/list` 分页列出历史 threads，可带过滤条件。
- `thread/read` 读取指定 thread 的当前状态和 metadata。
- `thread/fork` 从已有 thread 派生新 thread。

## Turn 示例

- `turn/start` 向 thread 提交新输入。
- `turn/steer` 在 turn 运行中追加 steering input。
- `turn/interrupt` 中断正在运行的 turn。

Turn 运行时会产生事件流，client 应逐步渲染事件，而不是只等待最终结果。

## Approval

当 Codex 需要用户授权时，server 会请求 client 决策。常见 approval 类型：

- 执行 shell 命令。
- 应用 patch。
- 授权特定路径或 root。

client 应明确返回 allow 或 deny，并把拒绝结果反馈给用户界面。

## Auth endpoints v2

认证相关 API 用于：

- 读取当前账号状态。
- 启动 ChatGPT 登录或 device-code 登录。
- 取消登录。
- 退出登录。
- 读取 rate limits。

## Config endpoints

Config API 允许读取和写入配置项。注意：config RPC payload 需要与 `config.toml` key 对齐，因此 wire 字段可能保留 snake_case，而不是统一 camelCase。

## Model list

`model/list` 返回当前 Codex build 可用模型目录，包括：

- 模型 id 和 display name。
- 支持的 reasoning efforts。
- 默认 reasoning effort。
- 输入 modalities。
- 是否为默认模型。
- 是否有推荐升级模型。

## 开发约束

新 app-server API 开发规则：

- 新 API surface 应添加到 v2，不要扩展 v1。
- 请求 payload 命名为 `*Params`。
- 响应命名为 `*Response`。
- 通知命名为 `*Notification`。
- RPC 方法使用 `<resource>/<method>`，resource 用单数。
- 除 config RPC 外，wire 字段默认 camelCase。
- v2 类型应设置 `#[ts(export_to = "v2/")]`。
- discriminated unions 需要在 serde 和 ts 两侧显式 tag。
- API 边界优先使用 plain `String` IDs。
- timestamp 使用 Unix seconds（`i64`），字段命名为 `*_at`。
- 新 list 方法默认采用 cursor pagination。

## 验证

API shape 或行为变化时：

- 更新 app-server docs/examples。
- 必要时运行 `just write-app-server-schema`。
- 涉及 experimental fixture 时运行 `just write-app-server-schema --experimental`。
- 运行 `just test -p codex-app-server-protocol`。
