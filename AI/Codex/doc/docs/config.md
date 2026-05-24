# 配置

> 原文：`AI/codex/docs/config.md`

基础配置说明请看：

`https://developers.openai.com/codex/config-basic`

高级配置说明请看：

`https://developers.openai.com/codex/config-advanced`

完整配置参考请看：

`https://developers.openai.com/codex/config-reference`

## 生命周期 Hook

管理员可以在 `requirements.toml` 顶层设置：

```toml
allow_managed_hooks_only = true
```

这个设置会忽略用户、项目和会话级 hook 配置，但仍允许 requirements 和 managed config 层中的 managed hooks。

该设置只支持放在 `requirements.toml` 中；放在 `config.toml` 中不会启用 managed-hooks-only 模式。
