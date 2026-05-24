# Codex 功能速查手册

> 来源：根据 `AI/codex` 下 README、[docs/*.md](doc/docs/README.md)、`codex-rs/**/README.md`、SDK 文档和相关提示模板整理。用途是忘记某个 Codex 功能、入口或文档位置时快速查询；不是入门安装教程。

## 快速入口

| 想做什么 | 入口 / 命令 | 参考文档 |
| --- | --- | --- |
| 打开交互式 Codex CLI | `codex` | [README.md](doc/README.md) |
| 打开桌面 App 体验 | `codex app` | [README.md](doc/README.md) |
| 非交互自动执行任务 | `codex exec "prompt"` | [codex-rs/README.md](doc/codex-rs/README.md)、[docs/exec.md](doc/docs/exec.md) |
| 临时覆盖配置 | `codex -c key=value` | [docs/config.md](doc/docs/config.md) |
| 使用指定 profile | `codex -p <profile>` | [codex-rs/responses-api-proxy/README.md](doc/codex-rs/responses-api-proxy/README.md) 示例 |
| 选择 sandbox 策略 | `codex --sandbox read-only/workspace-write/danger-full-access` | [codex-rs/README.md](doc/codex-rs/README.md) |
| 测试 sandbox 下命令行为 | `codex sandbox [COMMAND]...` | [codex-rs/README.md](doc/codex-rs/README.md) |
| 管理 MCP server 配置 | `codex mcp ...` | [codex-rs/README.md](doc/codex-rs/README.md) |
| 把 Codex 作为 MCP server | `codex mcp-server` | [codex-rs/docs/codex_mcp_interface.md](doc/codex-rs/docs/codex_mcp_interface.md) |
| 检查执行策略 | `codex execpolicy check --rules <file> <cmd>` | [codex-rs/execpolicy/README.md](doc/codex-rs/execpolicy/README.md) |
| 查看详细日志 | `codex -c log_dir=./.codex-log` | [docs/install.md](doc/docs/install.md) |

## 文档地图

| 主题 | 看哪里 |
| --- | --- |
| 官方功能总览 | [docs/getting-started.md](doc/docs/getting-started.md) 指向官方 Codex CLI features |
| 认证 | [docs/authentication.md](doc/docs/authentication.md) |
| 基础/高级/完整配置 | [docs/config.md](doc/docs/config.md) |
| 示例配置 | [docs/example-config.md](doc/docs/example-config.md) |
| Slash commands | [docs/slash_commands.md](doc/docs/slash_commands.md) |
| Sandbox 和 approvals | [docs/sandbox.md](doc/docs/sandbox.md) |
| Execution policy | [docs/execpolicy.md](doc/docs/execpolicy.md)、[codex-rs/execpolicy/README.md](doc/codex-rs/execpolicy/README.md) |
| Skills | [docs/skills.md](doc/docs/skills.md)、[codex-rs/skills/src/assets/samples/*](doc/codex-rs/skills/src/assets/samples/README.md) |
| AGENTS.md | [AGENTS.md](doc/AGENTS.md)、[docs/agents_md.md](doc/docs/agents_md.md) |
| 非交互模式 | [docs/exec.md](doc/docs/exec.md)、[codex-rs/README.md](doc/codex-rs/README.md) |
| 构建、测试、日志 | [docs/install.md](doc/docs/install.md)、[codex-rs/README.md](doc/codex-rs/README.md) |
| Rust CLI 架构 | [codex-rs/README.md](doc/codex-rs/README.md) |
| MCP server API | [codex-rs/docs/codex_mcp_interface.md](doc/codex-rs/docs/codex_mcp_interface.md) |
| App server API | [codex-rs/app-server/README.md](doc/codex-rs/app-server/README.md) |
| Python SDK | [sdk/python/README.md](doc/sdk/python/README.md)、[sdk/python/docs/*](doc/sdk/python/docs/README.md) |
| TypeScript SDK | [sdk/typescript/README.md](doc/sdk/typescript/README.md) |
| Memory 机制 | [codex-rs/memories/README.md](doc/codex-rs/memories/README.md) |
| Network proxy | [codex-rs/network-proxy/README.md](doc/codex-rs/network-proxy/README.md) |
| Responses API proxy | [codex-rs/responses-api-proxy/README.md](doc/codex-rs/responses-api-proxy/README.md) |

## CLI 常用功能

| 功能 | 速查 |
| --- | --- |
| 交互模式 | 运行 `codex`，适合日常结对改代码、问答、调试。 |
| 非交互模式 | `codex exec PROMPT`，适合脚本、CI、自动化任务。 |
| stdin 输入 | 可以把 stdin 拼到 prompt 后，例如 `echo "...日志..." | codex exec "总结"`。 |
| 无会话持久化 | `codex exec --ephemeral ...`，不写 session rollout 文件。 |
| 配置覆盖 | `-c key=value`，适合临时切换 provider、日志、sandbox 等配置。 |
| profile | `-p <profile>`，适合预设模型、provider、proxy、权限组合。 |
| 日志 | `-c log_dir=./.codex-log` 后查看 `codex-tui.log`。 |

## 配置速查

Codex Rust CLI 使用 `config.toml`，不是旧的 `config.json`。

常见配置方向：

- 模型和 model provider。
- sandbox / permissions profile。
- MCP server。
- lifecycle hooks。
- 通知脚本。
- log directory。
- network proxy。

临时覆盖示例：

```bash
codex -c log_dir=./.codex-log
```

```bash
codex exec -c model_provider="openai-proxy" "Your prompt here"
```

管理员可在 `requirements.toml` 设置：

```toml
allow_managed_hooks_only = true
```

该设置只在 `requirements.toml` 中生效，用于忽略用户、项目、会话 hook 配置，但保留 managed hooks。

## Sandbox 和权限

| 策略 | 用途 |
| --- | --- |
| `read-only` | 默认安全策略，只读工作区。 |
| `workspace-write` | 允许写当前 workspace，默认仍阻止网络；也允许写 `~/.codex/memories`。 |
| `danger-full-access` | 关闭 sandbox；只应在容器或其他隔离环境中使用。 |

命令：

```bash
codex --sandbox read-only
codex --sandbox workspace-write
codex --sandbox danger-full-access
```

测试某个命令在 sandbox 下会怎样：

```bash
codex sandbox [COMMAND]...
```

macOS 诊断 sandbox 拒绝：

```bash
codex sandbox --log-denials [COMMAND]...
```

## 执行策略 Execpolicy

Execpolicy 用规则决定命令是 `allow`、`prompt` 还是 `forbidden`。

规则核心：

- `prefix_rule(pattern=[...])`：按命令 token 前缀匹配。
- `decision`：`allow`、`prompt`、`forbidden`。
- `justification`：说明规则原因。
- `match` / `not_match`：规则自测样例。
- `host_executable(...)`：限制绝对路径程序回退到 basename 规则。

检查命令：

```bash
codex execpolicy check --rules path/to/policy.rules git status
```

格式化 JSON 输出：

```bash
codex execpolicy check --rules path/to/policy.rules --pretty git status
```

绝对路径回退 basename：

```bash
codex execpolicy check \
  --rules path/to/policy.rules \
  --resolve-host-executables \
  /usr/bin/git status
```

判断优先级：`forbidden` > `prompt` > `allow`。

## MCP

Codex 有两类 MCP 能力：

| 能力 | 用法 |
| --- | --- |
| MCP client | Codex 启动时连接配置好的 MCP servers。 |
| MCP server | 运行 `codex mcp-server`，让其他 MCP client 把 Codex 当工具调用。 |

启动 MCP server：

```bash
codex mcp-server
```

用 inspector 检查：

```bash
npx @modelcontextprotocol/inspector codex mcp-server
```

MCP server 暴露的主要 v2 RPC：

- Thread：`thread/start`、`thread/resume`、`thread/fork`、`thread/read`、`thread/list`
- Turn：`turn/start`、`turn/steer`、`turn/interrupt`
- Account：`account/read`、`account/login/start`、`account/logout`、`account/rateLimits/read`
- Config：`config/read`、`config/value/write`、`config/batchWrite`
- Model：`model/list`
- App：`app/list`
- Collaboration Mode：`collaborationMode/list`

Approvals 由 server 发给 client：

- `applyPatchApproval`
- `execCommandApproval`

客户端必须返回：

```json
{ "decision": "allow" }
```

或：

```json
{ "decision": "deny" }
```

## AGENTS.md

`AGENTS.md` 用于给 Codex 注入项目/目录级规则。

速记：

- 文档入口：[docs/agents_md.md](doc/docs/agents_md.md)
- 本仓库规则翻译：[AGENTS.md](doc/AGENTS.md)
- 官方说明：该文件指向 OpenAI Codex AGENTS.md 文档。
- `child_agents_md` feature flag 开启后，Codex 会附加 AGENTS.md 作用域和优先级说明。
- 适合写项目约束、测试命令、代码风格、禁止事项。

适合写入：

```markdown
# AGENTS.md

- 修改前先说明计划。
- 保持改动最小。
- 运行相关测试。
- 不要修改生成文件，除非任务明确要求。
```

## Skills

Skills 是可复用能力包。文档入口：

- [docs/skills.md](doc/docs/skills.md)
- 样例：[codex-rs/skills/src/assets/samples/](doc/codex-rs/skills/src/assets/samples/README.md)

内置样例方向：

| Skill | 用途 |
| --- | --- |
| `imagegen` | 图片生成/编辑工作流。 |
| `openai-docs` | 查询 OpenAI 官方文档、模型选择、迁移建议。 |
| `plugin-creator` | 创建 Codex 插件结构和 manifest。 |
| `skill-creator` | 创建或更新 skill。 |
| `skill-installer` | 安装 curated 或 GitHub skill。 |

什么时候做 Skill：

- 流程高频重复。
- 步骤稳定。
- 需要引用固定资源或脚本。
- 单句提示说不清。

什么时候不做：

- 一次性任务。
- 简单提示词就能完成。
- 流程还没稳定。

## Collaboration Modes

文档位置：[codex-rs/collaboration-mode-templates/templates/](doc/codex-rs/collaboration-mode-templates/templates/README.md)

| 模式 | 适用场景 |
| --- | --- |
| Default | 默认协作。能合理假设并执行，也能在必要时提问。 |
| Execute | 任务清楚时端到端执行，少问问题，做合理假设。 |
| Pair Programming | 和用户边讨论边调试、边实现。 |
| Plan | 只做计划，不修改 repo-tracked 文件；输出 decision-complete 计划。 |

Plan Mode 关键点：

- 可以读文件、搜索、做非破坏性验证。
- 不允许编辑文件、运行会修改 tracked 文件的格式化/生成命令。
- 最终计划用 `<proposed_plan>` 包裹。
- 计划必须足够明确，交给另一个工程师也能直接执行。

## Memory

文档位置：[codex-rs/memories/README.md](doc/codex-rs/memories/README.md)

Memory pipeline 在 root session 启动时后台运行，前提：

- session 不是 ephemeral。
- memory feature 开启。
- 不是 sub-agent session。
- state DB 可用。

两阶段：

| 阶段 | 作用 |
| --- | --- |
| Phase 1 | 从近期 eligible rollouts 中提取结构化 memory，写入 state DB。 |
| Phase 2 | 合并 stage-1 输出，更新 `~/.codex/memories` 下的 on-disk memory artifacts。 |

常见文件：

- `raw_memories.md`
- `rollout_summaries/`
- `phase2_workspace_diff.md`
- consolidated outputs，如 `MEMORY.md`、`memory_summary.md`、`skills/`

速记：

- `codex exec --ephemeral` 不持久化 session，因此不会走普通持久记忆路径。
- `workspace-write` 下 `~/.codex/memories` 是可写 root。
- Memory consolidation agent 无网络、无需 approvals、只允许本地写入。

## Hooks / Notifications

配置入口：[docs/config.md](doc/docs/config.md)、[codex-rs/README.md](doc/codex-rs/README.md)

常见用途：

- agent 完成 turn 后执行通知脚本。
- macOS 可通过 `terminal-notifier` 做桌面通知。
- WSL2 + Windows Terminal 下，TUI 会回退到 Windows toast notifications。
- 管理员可用 `allow_managed_hooks_only` 限制只运行 managed hooks。

## Network Proxy

文档位置：[codex-rs/network-proxy/README.md](doc/codex-rs/network-proxy/README.md)

用途：本地网络策略代理，提供 HTTP 和 SOCKS5 listener，并通过 allow/deny policy 限制网络访问。

默认：

- HTTP proxy：`127.0.0.1:3128`
- SOCKS5 proxy：`127.0.0.1:8081`

核心配置位于 selected permissions profile：

```toml
[permissions.workspace.network]
enabled = true
proxy_url = "http://127.0.0.1:3128"
enable_socks5 = true
socks_url = "http://127.0.0.1:8081"
mode = "full" # 或 "limited"
```

域名策略：

```toml
[permissions.workspace.network.domains]
"*.openai.com" = "allow"
"localhost" = "allow"
"evil.example" = "deny"
```

Limited mode：

- 只允许 `GET`、`HEAD`、`OPTIONS`。
- HTTPS `CONNECT` 需要 MITM 才能执行 method policy。
- SOCKS5 在 limited mode 下保持 blocked。

被拦截时常见响应：

- `blocked-by-allowlist`
- `blocked-by-denylist`
- `blocked-by-method-policy`
- `blocked-by-policy`

## Responses API Proxy

文档位置：[codex-rs/responses-api-proxy/README.md](doc/codex-rs/responses-api-proxy/README.md)

用途：严格代理 OpenAI Responses API，只允许：

```text
POST /v1/responses
```

其他请求返回 `403 Forbidden`。

典型用途：

- 由 privileged user 持有 `OPENAI_API_KEY` 启动代理。
- 非特权用户通过 local proxy 使用 Codex。
- 可 dump request/response 到目录方便调试。

配置 profile 示例：

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

## SDK 速查

### TypeScript SDK

文档位置：[sdk/typescript/README.md](doc/sdk/typescript/README.md)

用途：在工作流或应用里嵌入 Codex agent。SDK 会启动 `@openai/codex` CLI，并通过 stdin/stdout JSONL 交换事件。

常用能力：

- `startThread()`
- `thread.run(...)`
- `thread.runStreamed(...)`
- structured output with JSON Schema
- attach local images
- `resumeThread(threadId)`
- 控制 working directory
- 控制 CLI env
- 传入 config overrides

最小示例：

```typescript
import { Codex } from "@openai/codex-sdk";

const codex = new Codex();
const thread = codex.startThread();
const turn = await thread.run("Diagnose the test failure and propose a fix");

console.log(turn.finalResponse);
```

### Python SDK

文档位置：

- [sdk/python/README.md](doc/sdk/python/README.md)
- [sdk/python/docs/getting-started.md](doc/sdk/python/docs/getting-started.md)
- [sdk/python/docs/api-reference.md](doc/sdk/python/docs/api-reference.md)
- [sdk/python/docs/faq.md](doc/sdk/python/docs/faq.md)

用途：实验性 Python SDK，通过 `codex app-server` JSON-RPC v2 over stdio 控制 Codex。

常用能力：

- `Codex()`
- `thread_start(...)`
- `thread.run(...)`
- `thread.turn(...)`
- sync / async clients
- ChatGPT login / device-code login / API key login
- streaming、steering、interrupt control

最小示例：

```python
from openai_codex import Codex

with Codex() as codex:
    thread = codex.thread_start(model="gpt-5")
    result = thread.run("Say hello in one sentence.")
    print(result.final_response)
```

注意：

- `Codex()` 构造时会启动并 initialize app-server。
- 推荐用 context manager 确保 shutdown。
- `thread.run("...")` 适合常见场景。
- 需要 streaming、steering、interrupt 时用 `thread.turn(...)`。

## App Server / MCP Server API

内部或集成开发看：

- [codex-rs/app-server/README.md](doc/codex-rs/app-server/README.md)
- [codex-rs/docs/codex_mcp_interface.md](doc/codex-rs/docs/codex_mcp_interface.md)
- [codex-rs/docs/protocol_v1.md](doc/codex-rs/docs/protocol_v1.md)
- [codex-rs/protocol/README.md](doc/codex-rs/protocol/README.md)

重要概念：

- Thread：会话线程。
- Turn：一次用户输入和 agent 响应周期。
- Event stream：实时事件。
- Approval：执行命令或应用 patch 前的授权请求。
- v2 API 是新开发主线；v1 主要用于兼容。

App server v2 开发约束速记：

- 新 API 放 v2，不新增 v1 surface。
- 请求 payload 用 `*Params`，响应用 `*Response`，通知用 `*Notification`。
- RPC 方法形如 `<resource>/<method>`，resource 用单数。
- wire 字段默认 camelCase；config RPC 例外，保持 snake_case 对齐 `config.toml`。
- 新 list 方法默认做 cursor pagination。
- API shape 改动后更新 docs/examples，必要时跑 schema 生成和协议测试。

## 开发与测试速查

构建和测试主要在 `codex-rs` Cargo workspace。

常用命令：

```bash
just fmt
just fix -p <crate-you-touched>
just test -p <crate-you-touched>
just test
```

约束：

- 不要直接跑 `cargo test`，优先用 `just test`。
- 常规本地测试避免 `--all-features`。
- 改 Rust 代码后自动跑 `just fmt`。
- 大改前针对 touched crate 跑 `just fix -p <crate>`。
- UI 或文本输出变化需要更新 `insta` snapshots。
- 改 `ConfigToml` 或 nested config types 后运行 `just write-config-schema`。
- 改 Rust dependencies 后运行 `just bazel-lock-update` 和 `just bazel-lock-check`。

Snapshot 常用命令：

```bash
just test -p codex-tui
cargo insta pending-snapshots -p codex-tui
cargo insta show -p codex-tui path/to/file.snap.new
cargo insta accept -p codex-tui
```

## Apply Patch

文档位置：[codex-rs/apply-patch/apply_patch_tool_instructions.md](doc/codex-rs/apply-patch/apply_patch_tool_instructions.md)

Patch 结构：

```text
*** Begin Patch
*** Add File: path
+new line
*** Update File: path
@@
-old
+new
*** Delete File: path
*** End Patch
```

规则：

- 必须有 `*** Begin Patch` 和 `*** End Patch`。
- 每个文件操作必须是 Add / Update / Delete。
- Add File 的每一行都要以 `+` 开头。
- 文件路径只能是相对路径，不能是绝对路径。
- Update 可搭配 `*** Move to: <new path>` 重命名。

## Shell Escalation

文档位置：[codex-rs/shell-escalation/README.md](doc/codex-rs/shell-escalation/README.md)

作用：处理 sandbox shell 中命令是否在当前 sandbox 运行、升级到 sandbox 外运行或拒绝。

结果：

- `Run`：在 sandboxed shell 中执行原命令。
- `Escalate`：转发 fd，在 sandbox 外保真执行，返回 exit code。
- `Deny`：拒绝命令，stderr 输出错误并返回 1。

## 贡献与仓库规则

外部代码贡献目前只接受邀请。更推荐：

- 开 issue 描述新功能或行为变更。
- 给 bug report 补 reproduction、分析、根因假设。
- 在 issue 中讨论方案。

被邀请提交 PR 时：

- 从 `main` 建 topic branch。
- 保持改动聚焦。
- bug fix 应有有效测试。
- 用户可见行为变化要更新 README、inline help 或示例。
- 本地跑相关 `just` 检查。
- CLA 签署方式是在 PR 中评论：

```text
I have read the CLA Document and I hereby sign the CLA
```

安全问题联系：

```text
security@openai.com
```

## 功能遗忘时怎么找

| 忘了什么 | 先看 |
| --- | --- |
| Codex CLI 怎么运行某类任务 | [codex-rs/README.md](doc/codex-rs/README.md) |
| 某个配置项在哪 | [docs/config.md](doc/docs/config.md)、[docs/example-config.md](doc/docs/example-config.md) |
| 如何限制命令执行 | [codex-rs/execpolicy/README.md](doc/codex-rs/execpolicy/README.md) |
| sandbox 选哪个 | 本手册“Sandbox 和权限” |
| MCP server 有哪些 RPC | [codex-rs/docs/codex_mcp_interface.md](doc/codex-rs/docs/codex_mcp_interface.md) |
| app-server 事件/API | [codex-rs/app-server/README.md](doc/codex-rs/app-server/README.md) |
| Python 集成 | [sdk/python/docs/getting-started.md](doc/sdk/python/docs/getting-started.md) |
| TypeScript 集成 | [sdk/typescript/README.md](doc/sdk/typescript/README.md) |
| 为什么 memory 没跑 | 本手册“Memory” |
| 网络为什么被挡 | [codex-rs/network-proxy/README.md](doc/codex-rs/network-proxy/README.md) |
| 如何调试 Responses API 请求 | [codex-rs/responses-api-proxy/README.md](doc/codex-rs/responses-api-proxy/README.md) |
| Rust 改完跑什么 | 本手册“开发与测试速查” |
