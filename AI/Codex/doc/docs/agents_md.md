# AGENTS.md

> 原文：`AI/codex/docs/agents_md.md`

AGENTS.md 说明请看官方文档：

`https://developers.openai.com/codex/guides/agents-md`

## 层级化 agents message

启用 `child_agents_md` feature flag 后（通过 `config.toml` 的 `[features]`），Codex 会在用户指令消息中附加关于 AGENTS.md 作用域和优先级的额外指导；即使没有 AGENTS.md，也会发出这段消息。
