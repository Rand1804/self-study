# codex-execpolicy

> 原文：`AI/codex/codex-rs/execpolicy/README.md`

## 概览

- Policy engine 和 CLI 基于 `prefix_rule(pattern=[...], decision?, justification?, match?, not_match?)` 以及 `host_executable(name=..., paths=[...])`。
- 当前版本覆盖 execpolicy 语言中的 prefix-rule 子集和 host executable metadata；更丰富的语言会后续加入。
- Tokens 按顺序匹配；`pattern` 中任意元素可以是 list，表示可选项。`decision` 默认是 `allow`，合法值为 `allow`、`prompt`、`forbidden`。
- `justification` 是可选的人类可读解释，说明规则存在原因。任何 `decision` 都可提供。若使用 `forbidden`，合适时应包含推荐替代方案。
- `match` / `not_match` 提供加载时校验的示例调用，可视为规则单元测试。示例可以是 token 数组或字符串（字符串用 `shlex` tokenization）。
- CLI 总是打印 evaluation result 的 JSON 序列化。
- 旧规则匹配器位于 `codex-execpolicy-legacy`。

## Policy 形状

Prefix rules 使用 Starlark 语法：

```starlark
prefix_rule(
    pattern = ["cmd", ["alt1", "alt2"]],
    decision = "prompt", # allow | prompt | forbidden，默认 allow
    justification = "explain why this rule exists",
    match = [["cmd", "alt1"], "cmd alt2"],
    not_match = [["cmd", "oops"], "cmd alt3"],
)
```

Host executable metadata 可限制哪些绝对路径能通过 basename 规则解析：

```starlark
host_executable(
    name = "git",
    paths = [
        "/opt/homebrew/bin/git",
        "/usr/bin/git",
    ],
)
```

匹配语义：

- execpolicy 总是先尝试 exact first-token match。
- 禁用 host-executable resolution 时，`/usr/bin/git status` 只匹配第一个 token 为 `/usr/bin/git` 的规则。
- 启用 host-executable resolution 时，如果没有 exact rule match，execpolicy 可能从 `/usr/bin/git` 回退到 `git` 的 basename 规则。
- 如果存在 `host_executable(name="git", ...)`，basename fallback 只允许列出的绝对路径。
- 如果某个 basename 没有 `host_executable()` entry，则允许 basename fallback。

## CLI

检查命令：

```bash
codex execpolicy check --rules path/to/policy.rules git status
```

启用 basename fallback：

```bash
codex execpolicy check \
  --rules path/to/policy.rules \
  --resolve-host-executables \
  /usr/bin/git status
```

可传多个 `--rules` 合并规则，按提供顺序评估；用 `--pretty` 输出格式化 JSON。

开发时可直接运行独立 dev binary：

```bash
cargo run -p codex-execpolicy -- check --rules path/to/policy.rules git status
```

示例结果：

- 匹配：`{"matchedRules":[{...}],"decision":"allow"}`
- 不匹配：`{"matchedRules":[]}`

## 响应形状

```json
{
  "matchedRules": [
    {
      "prefixRuleMatch": {
        "matchedPrefix": ["<token>", "..."],
        "decision": "allow|prompt|forbidden",
        "resolvedProgram": "/absolute/path/to/program",
        "justification": "..."
      }
    }
  ],
  "decision": "allow|prompt|forbidden"
}
```

- 没有规则匹配时，`matchedRules` 为空数组，省略 `decision`。
- `matchedRules` 列出每条前缀匹配的规则。
- `resolvedProgram` 仅在绝对可执行路径通过 basename fallback 匹配时出现。
- 有效 `decision` 采用所有匹配中的最严格级别：`forbidden` > `prompt` > `allow`。

注意：`execpolicy` 命令仍处于 preview，将来 API 可能有破坏性变更。
