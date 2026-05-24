# Skills 样例索引

> 原始目录：`AI/codex/codex-rs/skills/src/assets/samples/`

该目录包含 Codex skills 的样例实现，主要用于演示 skill 的组织方式、触发规则、资源引用和脚本复用。

## 样例

| Skill | 作用 |
| --- | --- |
| `imagegen` | 图片生成和编辑工作流。 |
| `openai-docs` | 查询 OpenAI 官方文档、模型选择、迁移和 prompt 指南。 |
| `plugin-creator` | 创建 Codex 插件目录、manifest 和 marketplace 条目。 |
| `skill-creator` | 创建或更新 Codex skill。 |
| `skill-installer` | 安装 curated skill 或 GitHub skill。 |

## 使用建议

- 需要创建新 skill 时先看 `skill-creator/SKILL.md`。
- 需要创建插件时看 `plugin-creator/SKILL.md` 和其 references。
- 需要图片生成能力时看 `imagegen/SKILL.md`。
- 需要官方 OpenAI 文档查询时看 `openai-docs/SKILL.md`。
