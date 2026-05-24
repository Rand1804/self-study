# Memories

> 原文：`AI/codex/codex-rs/memories/README.md`

该目录拥有可复用的 memory crates 和 memory pipeline 文档。

Phase 1 和 Phase 2 的运行时 orchestration 仍位于 `codex-core` 的 `codex-rs/core/src/memories/` 下。

## Crates

- `codex-rs/memories/read`（`codex-memories-read`）：负责 read path，包括 memory developer-instruction injection、memory citation parsing、read-usage telemetry classification。
- `codex-rs/memories/mcp`（`codex-memories-mcp`）：负责只读 memory filesystem MCP server 实现。
- `codex-rs/memories/write`（`codex-memories-write`）：负责 write path，包括 Phase 1/2 prompt rendering、filesystem artifact helpers、workspace diff helpers、extension resource pruning。

## Prompt Templates

Memory prompt templates 位于使用它们的 crate 中。未带日期的模板文件是运行时使用的 canonical latest versions：

- `read/templates/memories/read_path.md`
- `write/templates/memories/stage_one_system.md`
- `write/templates/memories/stage_one_input.md`
- `write/templates/memories/consolidation.md`

在 `codex` 中直接编辑这些未带日期的模板文件。带日期 snapshot-copy workflow 用于另一个 harness repo，不用于这里。

## 何时运行

Pipeline 在 root session 启动时触发，但仅当：

- session 不是 ephemeral；
- memory feature 已启用；
- session 不是 sub-agent session；
- state DB 可用。

它会在后台异步运行，并按顺序执行 Phase 1 和 Phase 2。

## Phase 1：Rollout Extraction（per-thread）

Phase 1 查找近期 eligible rollouts，并从每个 rollout 提取结构化 memory。

实践中，候选 rollouts 需要：

- 来自允许的 interactive session sources；
- 位于配置的 age window 内；
- idle 时间足够长，以避免总结仍活跃或刚结束的 rollout；
- 尚未被其他 in-flight phase-1 worker 拥有；
- 位于 startup scan/claim limits 内。

它会：

- 从 state DB claim 有界数量的 rollout jobs；
- 将 rollout content 过滤为 memory-relevant response items；
- 并行发送每个 rollout 到模型（有 concurrency cap）；
- 期望结构化输出：`raw_memory`、`rollout_summary`、可选 `rollout_slug`；
- 从生成的 memory fields 中 redact secrets；
- 将成功输出作为 stage-1 outputs 写回 state DB。

Phase 1 的 job outcomes：

- `succeeded`：生成了 memory；
- `succeeded_no_output`：运行有效但没有有用输出；
- `failed`：失败并带 retry backoff/lease handling。

## Phase 2：Global Consolidation

Phase 2 将最新 stage-1 outputs 合并到 filesystem memory artifacts，然后运行专用 consolidation agent。

它会：

- claim 全局 phase-2 lock，确保同一时间只有一个 consolidation 检查或修改 memories root；
- 按选择规则从 state DB 加载有界 stage-1 outputs；
- 计算 completion watermark；
- 同步 `~/.codex/memories` 下的 local memory artifacts：
  - `raw_memories.md`
  - `rollout_summaries/`
- 维护 memories root 下的 git-baseline directory（`~/.codex/memories/.git`）；
- 删除不再选择的 stale rollout summaries；
- 删除超过 retention window 的 memory extension resource files；
- 写入 `phase2_workspace_diff.md`，包含自上次成功 Phase 2 baseline 以来的 git-style diff；
- 如果 memory workspace 没有变化，则标记成功并退出。

如果 workspace 有变化，它会：

- 启动内部 consolidation sub-agent；
- 用 workspace diff 路径构建 Phase 2 prompt；
- 指向 `phase2_workspace_diff.md` 提供详细 diff context；
- 以无 approvals、无网络、仅本地写权限运行；
- 禁用 collab，避免递归 delegation；
- 监控 agent 状态并续租 global job lease；
- agent 成功后重置 memory git baseline；
- 删除生成的 diff 文件，避免把删除内容保留在 prompt artifact 或不可达 git objects 中；
- 记录 phase-2 job 成功或失败。

## 为什么拆成两阶段

- Phase 1 可跨多个 rollouts 扩展，并生成规范化的 per-rollout memory records。
- Phase 2 将全局 consolidation 串行化，安全且一致地更新共享 memory artifacts。
