# 贡献

> 原文：`AI/codex/docs/contributing.md`

**外部贡献目前仅接受邀请。**

Codex 团队当前不接受未邀请的代码贡献。

如果你想提出新功能或行为变更，请打开 issue 描述提案，或为已有增强请求点赞。团队会根据社区反馈、路线图一致性，以及 CLI、IDE 扩展、Web 等 Codex 各端体验的一致性来安排优先级。

如果你遇到 bug，请提交 bug report，或确认已有报告是否覆盖了该问题。欢迎在 issue 中分享分析、复现步骤、根因假设或高层修复思路。

Codex 团队可能在以下情况下邀请外部贡献者提交 PR：

- 问题已经被充分理解；
- 方案与团队预期方向一致；
- 问题影响大且优先级高。

未经团队成员明确邀请的 PR 会被关闭且不进入 review。

## 开发工作流

如果你被邀请贡献 PR，推荐流程：

- 从 `main` 创建 topic branch，例如 `feat/interactive-prompt`。
- 保持变更聚焦；多个无关修复应拆成多个 PR。
- 确保没有 lint warning 和测试失败。

## 被邀请代码贡献的指导

1. **从 issue 开始。** 新开 issue 或评论现有讨论，先就方案达成一致。
2. **添加或更新测试。** Bug fix 通常应包含测试覆盖，能在修复前失败、修复后通过。
3. **记录行为。** 如果变更影响用户可见行为，请更新 README、inline help（`codex --help`）或相关示例项目。
4. **保持提交原子化。** 每个 commit 都应能编译并通过测试，方便 review 和回滚。

## 模型元数据更新

如果变更更新模型目录或模型元数据（`/models` payload、presets 或 fixtures）：

- 对不支持图片的模型显式设置 `input_modalities`。
- 注意兼容默认值：省略 `input_modalities` 当前意味着支持文本 + 图片。
- 确保接收图片的客户端界面（例如 TUI paste/attach）使用同一能力信号。
- 添加或更新测试，覆盖不支持图片时的行为和 warning 路径。

## 打开 PR（仅限邀请）

- 填写 PR 模板，或包含类似信息：**What? Why? How?**
- 链接相关 bug report 或 enhancement request。
- 本地运行所有检查；使用根 `just` helper：`just fmt`、`just fix -p <crate>`，以及相关测试（如 `just test -p codex-tui`，必要时 `just test`）。
- 确保分支基于最新 `main`，并已解决冲突。
- 只有在你认为 PR 可合并时才标记为 Ready for review。

## Review 流程

1. 一名 maintainer 会被指定为 primary reviewer。
2. 如果邀请 PR 引入了未讨论并批准的范围或行为，可能会被关闭。
3. 团队可能要求修改。
4. 达成一致后，maintainer 会 squash-and-merge。

## 社区价值观

- **友善和包容。** 尊重他人，遵循 Contributor Covenant。
- **假设善意。** 书面沟通容易误解，尽量宽容理解。
- **教学相长。** 如果发现困惑点，请通过 issue 或 discussion 给出建议或澄清。

## 获取帮助

如果设置项目遇到问题、想获得想法反馈，或只是打个招呼，请打开 Discussion 或加入相关 issue。

## CLA

所有贡献者必须接受 CLA。流程很轻：

1. 打开 PR。
2. 粘贴以下评论，或如果以前签过则回复 `recheck`：

```text
I have read the CLA Document and I hereby sign the CLA
```

3. CLA-Assistant bot 会记录签名并将状态检查标记为通过。

不需要特殊 Git 命令、邮件附件或 commit footer。

## 安全与负责任 AI

如果你发现漏洞或对模型输出有担忧，请发送邮件至 `security@openai.com`。
