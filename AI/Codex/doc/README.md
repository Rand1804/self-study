# Codex CLI

> 原文：`AI/codex/README.md`

**Codex CLI** 是 OpenAI 提供的本地代码智能体，运行在你的电脑上。

如果你想在代码编辑器中使用 Codex（VS Code、Cursor、Windsurf），请安装 IDE 版本。  
如果你想使用桌面 App 体验，可以运行 `codex app`，或访问 Codex App 页面。  
如果你要找的是 OpenAI 的云端智能体 **Codex Web**，请访问 `chatgpt.com/codex`。

## 快速开始

### 安装和运行 Codex CLI

Mac 或 Linux：

```shell
curl -fsSL https://chatgpt.com/codex/install.sh | sh
```

Windows：

```powershell
powershell -ExecutionPolicy ByPass -c "irm https://chatgpt.com/codex/install.ps1 | iex"
```

也可以通过包管理器安装：

```shell
npm install -g @openai/codex
```

```shell
brew install --cask codex
```

然后运行：

```shell
codex
```

也可以到 GitHub 最新 Release 下载对应平台的二进制文件。常用包包括：

- macOS Apple Silicon/arm64：`codex-aarch64-apple-darwin.tar.gz`
- macOS x86_64：`codex-x86_64-apple-darwin.tar.gz`
- Linux x86_64：`codex-x86_64-unknown-linux-musl.tar.gz`
- Linux arm64：`codex-aarch64-unknown-linux-musl.tar.gz`

每个压缩包里通常只有一个带平台名的可执行文件，解压后一般需要重命名为 `codex`。

### 使用 ChatGPT 计划登录 Codex

运行 `codex` 后选择 **Sign in with ChatGPT**。推荐用 ChatGPT 账号登录，这样可以使用 Plus、Pro、Business、Edu 或 Enterprise 计划中的 Codex 权益。

也可以用 API key 使用 Codex，但需要额外配置。

## 文档

- Codex Documentation：`https://developers.openai.com/codex`
- Contributing：`docs/contributing.md`
- Installing & building：`docs/install.md`
- Open source fund：`docs/open-source-fund.md`

本仓库使用 Apache-2.0 License。
