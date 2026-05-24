# 安装与构建

> 原文：`AI/codex/docs/install.md`

## 系统要求

| 要求 | 细节 |
| --- | --- |
| 操作系统 | macOS 12+、Ubuntu 20.04+/Debian 10+，或通过 WSL2 使用 Windows 11 |
| Git（可选但推荐） | 2.23+，用于内置 PR 辅助功能 |
| RAM | 最低 4GB，推荐 8GB |

## DotSlash

GitHub Release 中也包含名为 `codex` 的 DotSlash 文件。使用 DotSlash 文件，可以在源码控制中轻量提交一个固定入口，确保所有贡献者在不同平台上使用同一版本的可执行文件。

## 从源码构建

```bash
# 克隆仓库并进入 Cargo workspace 根目录。
git clone https://github.com/openai/codex.git
cd codex/codex-rs

# 如有必要，安装 Rust toolchain。
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
source "$HOME/.cargo/env"
rustup component add rustfmt
rustup component add clippy
# 安装 workspace justfile 使用的辅助工具。
cargo install --locked just
# 安装 `just test` 使用的 nextest。
cargo install --locked cargo-nextest

# 构建 Codex。
cargo build

# 用示例 prompt 启动 TUI。
cargo run --bin codex -- "explain this codebase to me"

# 修改后使用根 justfile helpers（默认作用于 codex-rs）。
just fmt
just fix -p <crate-you-touched>

# 运行相关测试，例如：
just test -p codex-tui
# `just test` 通过 nextest 运行测试套件：
just test
# 常规本地运行避免 `--all-features`，因为它会扩大构建矩阵，增加构建时间和 target/ 磁盘占用。
```

## Tracing / verbose logging

Codex 用 Rust 编写，因此遵循 `RUST_LOG` 环境变量来配置日志行为。

TUI 默认把诊断信息记录到有界本地存储中。可以显式设置 `log_dir`，为一次运行启用明文 TUI 日志：

```bash
codex -c log_dir=./.codex-log
tail -F ./.codex-log/codex-tui.log
```

非交互模式（`codex exec`）默认使用 `RUST_LOG=error`，但消息会直接内联打印到终端，因此不需要监控单独日志文件。

更多配置可参考 Rust `RUST_LOG` 文档。
