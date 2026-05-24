# Codex CLI（Rust 实现）

> 原文：`AI/codex/codex-rs/README.md`

Codex CLI 作为独立可执行文件发布，以实现零依赖安装。

## 安装 Codex

目前最简单的安装方式是 npm：

```shell
npm i -g @openai/codex
codex
```

也可以通过 Homebrew 安装：

```shell
brew install --cask codex
```

或从 GitHub Releases 下载平台对应的发布包。

## 文档快速入口

- 第一次运行 Codex：看 `docs/getting-started.md`，其中链接到 prompt、快捷键和 session 管理 walkthrough。
- 想深入控制：看 `docs/config.md` 和 `docs/install.md`。

## Rust CLI 新内容

Rust 实现现在是维护中的 Codex CLI，也是默认体验。它包含一些旧 TypeScript CLI 不支持的功能。

### 配置

Codex 支持丰富配置项。Rust CLI 使用 `config.toml`，不是 `config.json`。

### Model Context Protocol 支持

#### MCP client

Codex CLI 可以作为 MCP client，在启动时让 CLI 和 IDE extension 连接 MCP servers。配置详见配置文档中的 MCP servers 部分。

#### MCP server（实验性）

可以运行：

```shell
codex mcp-server
```

把 Codex 作为 MCP server 启动，让其他 MCP client 把 Codex 当作另一个 agent 的工具。

可用 inspector 测试：

```shell
npx @modelcontextprotocol/inspector codex mcp-server
```

使用 `codex mcp` 添加、列出、获取或删除 `config.toml` 中定义的 MCP server launcher；使用 `codex mcp-server` 直接运行 MCP server。

### 通知

可配置一个脚本，在 agent 完成一次 turn 时运行。macOS 可通过 `terminal-notifier` 获取桌面通知。若 Codex 检测到运行在 WSL 2 的 Windows Terminal 中，TUI 会自动回退到原生 Windows toast notifications，使审批提示和完成通知能够浮现。

### `codex exec` 非交互/程序化运行

运行：

```shell
codex exec PROMPT
```

Codex 会非交互地处理任务，直到判断完成并退出。也可以从 stdin 传入 prompt。如果同时提供 prompt 参数和 piped stdin，Codex 会把 stdin 作为 `<stdin>` block 追加到 prompt 后。

使用：

```shell
codex exec --ephemeral ...
```

可避免把 session rollout 文件持久化到磁盘。

### 试验 Codex Sandbox

测试某条命令在 Codex sandbox 中的行为：

```shell
codex sandbox [COMMAND]...
```

该命令会使用当前宿主系统的 sandbox 实现：macOS 是 Seatbelt，Linux 是 Linux sandbox，Windows 是 restricted token。

macOS 专用诊断参数：

```shell
codex sandbox --log-denials [COMMAND]...
```

`codex sandbox` 也接受 `--profile NAME`（或 `-p NAME`），把 `$CODEX_HOME/NAME.config.toml` 叠加到基础用户配置上。

### 通过 `--sandbox` 选择 sandbox policy

```shell
codex --sandbox read-only
codex --sandbox workspace-write
codex --sandbox danger-full-access
```

- `read-only`：默认只读 sandbox。
- `workspace-write`：允许 agent 写当前 workspace，同时仍阻止网络访问。
- `danger-full-access`：禁用 sandbox。仅在已处于容器或其他隔离环境时使用。

在 `workspace-write` 下，Codex 也会把 `~/.codex/memories` 放入 writable roots，维护 memory 时无需额外 approval。

## 代码组织

该目录是 Cargo workspace 根目录。关键 crate：

- `core/`：Codex 业务逻辑。
- `exec/`：用于自动化的 headless CLI。
- `tui/`：基于 Ratatui 的 fullscreen TUI。
- `cli/`：多工具 CLI，通过子命令提供上述 CLI。

如果要贡献或深入查看行为，先阅读各 crate 下的模块级 `README.md`，并从顶层 `codex-rs` 目录运行 workspace，以保持共享配置、features 和构建脚本一致。
