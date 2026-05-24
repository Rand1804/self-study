# Codex SDK

> 原文：`AI/codex/sdk/typescript/README.md`

在工作流和应用中嵌入 Codex agent。

TypeScript SDK 封装 `@openai/codex` 中的 `codex` CLI。它会启动 CLI，并通过 stdin/stdout 交换 JSONL events。

## 安装

```bash
npm install @openai/codex-sdk
```

需要 Node.js 18+。

## 快速开始

```typescript
import { Codex } from "@openai/codex-sdk";

const codex = new Codex();
const thread = codex.startThread();
const turn = await thread.run("Diagnose the test failure and propose a fix");

console.log(turn.finalResponse);
console.log(turn.items);
```

在同一个 `Thread` 实例上重复调用 `run()` 可继续同一对话：

```typescript
const nextTurn = await thread.run("Implement the fix");
```

## Streaming responses

`run()` 会缓存事件直到 turn 完成。如果要响应中间进度（tool calls、streaming responses、file change notifications），使用 `runStreamed()`。它返回结构化事件的 async generator。

## Structured output

Codex agent 可生成符合指定 JSON schema 的 JSON 响应。schema 可作为 plain JSON object 传给每个 turn。

也可以用 `zod-to-json-schema` 从 Zod schema 生成 JSON schema，并将 `target` 设为 `openAi`。

## 附加图片

需要同时包含图片和文本时，传入 structured input entries。Text entries 会被拼接到最终 prompt，image entries 会通过 `--image` 传给 Codex CLI。

```typescript
const turn = await thread.run([
  { type: "text", text: "Describe these screenshots" },
  { type: "local_image", path: "./ui.png" },
  { type: "local_image", path: "./diagram.jpg" },
]);
```

## 恢复已有 thread

Threads 持久化在 `~/.codex/sessions`。如果内存中的 `Thread` 对象丢失，可用 `resumeThread()` 恢复。

```typescript
const savedThreadId = process.env.CODEX_THREAD_ID!;
const thread = codex.resumeThread(savedThreadId);
await thread.run("Implement the fix");
```

## 工作目录控制

Codex 默认在当前工作目录运行。为了避免不可恢复错误，Codex 要求工作目录是 Git repo。创建 thread 时传 `skipGitRepoCheck` 可以跳过检查。

```typescript
const thread = codex.startThread({
  workingDirectory: "/path/to/project",
  skipGitRepoCheck: true,
});
```

## 控制 Codex CLI 环境

默认情况下，Codex CLI 继承 Node.js 进程环境。实例化 `Codex` client 时可传 `env` 参数完全控制 CLI 接收的环境变量，适合 Electron 等 sandboxed host。

SDK 会在你提供的环境之上注入必要变量（如 `CODEX_API_KEY`）。如果设置 `baseUrl`，SDK 会把它作为 `--config openai_base_url=...` 覆盖传入。

## 传递 `--config` overrides

用 `config` 选项提供额外 Codex CLI 配置覆盖。SDK 接受 JSON object，将其 flatten 为 dotted paths，并把值序列化为 TOML literals 后作为重复 `--config key=value` flags 传入。

Thread options 对重叠设置优先级更高，因为它们在 global overrides 之后发出。
