# Rust/codex-rs

> 原文：`AI/codex/AGENTS.md`

在 Rust 代码所在的 `codex-rs` 文件夹中：

- Crate 名称都以 `codex-` 为前缀。例如，`core` 文件夹对应的 crate 名为 `codex-core`。
- 使用 `format!` 时，如果可以把变量内联到 `{}` 中，就始终这样做。
- 如果运行这里的指令需要仓库依赖的命令（例如 `just`、`rg` 或 `cargo-insta`），而这些命令尚未安装，请先安装。
- 永远不要添加或修改任何与 `CODEX_SANDBOX_NETWORK_DISABLED_ENV_VAR` 或 `CODEX_SANDBOX_ENV_VAR` 相关的代码。
  - 你运行在一个 sandbox 中，每当使用 `shell` 工具时都会设置 `CODEX_SANDBOX_NETWORK_DISABLED=1`。现有使用 `CODEX_SANDBOX_NETWORK_DISABLED_ENV_VAR` 的代码是在了解这一事实的前提下编写的。它通常用于让作者知道你由于 sandbox 限制无法运行的测试提前退出。
  - 类似地，当你使用 Seatbelt（`/usr/bin/sandbox-exec`）启动进程时，子进程会设置 `CODEX_SANDBOX=seatbelt`。想自行运行 Seatbelt 的集成测试不能在 Seatbelt 之下运行，因此对 `CODEX_SANDBOX=seatbelt` 的检查也常用于让测试按需提前退出。
- 始终按 clippy 规则折叠 if 语句：https://rust-lang.github.io/rust-clippy/master/index.html#collapsible_if
- 只要可能，始终按 clippy 规则内联 `format!` 参数：https://rust-lang.github.io/rust-clippy/master/index.html#uninlined_format_args
- 只要可能，用方法引用代替闭包：https://rust-lang.github.io/rust-clippy/master/index.html#redundant_closure_for_method_calls
- 避免使用 bool 或含糊的 `Option` 参数，因为它们会迫使调用者写出难读的代码，例如 `foo(false)` 或 `bar(None)`。当能让调用点保持自解释时，优先使用 enum、命名方法、newtype 或其他符合 Rust 习惯的 API 形状。
- 当无法做这种 API 改动，但仍需要在 Rust 中使用小型位置字面量调用点时，请遵循 `argument_comment_lint` 约定：
  - 在按位置传递 `None`、布尔值和数字字面量等不透明 literal 参数前，使用精确的 `/*param_name*/` 注释。
  - 不要给字符串或字符 literal 添加这些注释，除非注释确实增加了清晰度；这些 literal 有意豁免于该 lint。
  - 注释中的参数名必须与被调用函数签名完全一致。
  - 可以运行 `just argument-comment-lint` 在本地执行 lint 检查。它由 Bazel 驱动，因此第一次运行时如果 Bazel 未预热可能较慢，但增量运行通常应少于 15 秒。多数情况下，最好更新 PR，让 CI 负责检查，或在提交 PR 后异步后台运行。注意 CI 会检查三个平台，而本地运行不会。
- 只要可能，让 `match` 语句穷尽匹配，并避免 wildcard arms。
- 新增 trait 应包含 doc comments，解释其角色以及 implementation 应如何使用它。
- 不鼓励在 Rust trait 中使用 `#[async_trait]` 和 `#[allow(async_fn_in_trait)]`。
  - 优先使用 native RPITIT trait methods，并在返回的 future 上显式加 `Send` bounds，例如 `3c7f013f9735` / `#16630` 中的写法。
  - 推荐 trait 形状：
    `fn foo(&self, ...) -> impl std::future::Future<Output = T> + Send;`
  - 当 implementation 满足该 contract 时，仍可使用 `async fn foo(&self, ...) -> T`。
  - 不要用 `#[allow(async_fn_in_trait)]` 作为绕过显式 future contract 写法的捷径。
- 写测试时，优先比较整个对象是否相等，而不是逐字段比较。
- 不要向 `docs/` 文件夹添加通用产品文档或面向用户的文档。官方 Codex 文档位于其他地方。例外是 app-server API 文档，它由下面的 app-server 指南覆盖。
- 优先使用私有模块，并显式导出 public crate API。
- 如果修改 `ConfigToml` 或嵌套 config types，请运行 `just write-config-schema` 来更新 `codex-rs/core/config.schema.json`。
- 处理 MCP tool calls 时，优先使用 `codex-rs/codex-mcp/src/mcp_connection_manager.rs` 来处理 tools 和 tool calls 的变更。目标是缩小改动范围，并利用现有抽象，而不是把代码贯穿多层函数调用。
- 不要不必要地调用 `reset_client_session`；让 incremental check 逻辑决定是否复用前一个 request。
- 如果修改 Rust dependencies（`Cargo.toml` 或 `Cargo.lock`），请从 repo root 运行 `just bazel-lock-update` 来刷新 `MODULE.bazel.lock`，并把该 lockfile 更新包含在同一变更中。
- dependency 变更后，从 repo root 运行 `just bazel-lock-check`，以便在 CI 前本地捕捉 lockfile drift。
- Bazel 不会自动让 source-tree 文件可用于 Rust 编译期文件访问。如果添加 `include_str!`、`include_bytes!`、`sqlx::migrate!` 或类似的 build-time 文件/目录读取，请更新该 crate 的 `BUILD.bazel`（`compile_data`、`build_script_data` 或 test data），否则即使 Cargo 通过，Bazel 也可能失败。
- 不要创建只被引用一次的小 helper methods。
- 避免大型模块：
  - 优先新增模块，而不是继续扩大现有模块。
  - Rust 模块目标控制在 500 LoC 以下，不含测试。
  - 如果文件超过约 800 LoC，除非有充分且记录下来的理由，否则应把新功能放到新模块中，而不是继续扩展该文件。
  - 该规则尤其适用于容易吸引无关变更的高频文件，例如 `codex-rs/tui/src/app.rs`、`codex-rs/tui/src/bottom_pane/chat_composer.rs`、`codex-rs/tui/src/bottom_pane/footer.rs`、`codex-rs/tui/src/chatwidget.rs`、`codex-rs/tui/src/bottom_pane/mod.rs`，以及类似的核心 orchestration 模块。
  - 从大型模块中抽取代码时，把相关测试和模块/type 文档移到新的实现附近，让不变量靠近其所属代码。
  - 除非改动很小，否则避免向 `codex-rs/tui/src/chatwidget.rs` 添加新的独立方法；优先使用新模块/文件，并让 `chatwidget.rs` 专注于 orchestration。
- 运行 Rust 命令（例如 `just fix` 或 `just test`）时，请耐心等待命令完成，永远不要尝试用 PID 杀死它们。Rust lock 可能导致执行较慢，这是预期情况。

完成 Rust 代码修改后，自动在 `codex-rs` 目录中运行 `just fmt`；不要请求批准再运行它。另外，运行测试：

1. 不要直接运行 `cargo test`。使用 `just test`，让测试执行遵循仓库默认设置。
2. 运行被修改项目对应的测试。例如，如果修改了 `codex-rs/tui`，运行 `just test -p codex-tui`。
3. 这些测试通过后，如果修改了 common、core 或 protocol 中的任何内容，请用 `just test` 运行完整测试套件。常规本地运行避免 `--all-features`，因为它会扩大构建矩阵，并显著增加 `target/` 磁盘占用；只有在明确需要完整 feature coverage 时才使用。项目级或单个测试可以不询问用户直接运行，但运行完整测试套件前请询问用户。

在完成 `codex-rs` 的大型变更前，在 `codex-rs` 目录中运行 `just fix -p <project>` 来修复代码中的 linter 问题。优先用 `-p` 限定范围，避免缓慢的 workspace-wide Clippy 构建；只有修改了共享 crates 时才运行不带 `-p` 的 `just fix`。运行 `fix` 或 `fmt` 后不要重新运行测试。

## `codex-core` crate

随着时间推移，`codex-core` crate（定义于 `codex-rs/core/`）已经变得臃肿。由于它是最大的 crate，通常往 `codex-core` 中添加新东西会比重构出所需库代码更容易，但这样会让你的新代码既依赖 `codex-core`，又继续增加 `codex-core` 的体积。

因此：**抵制向 codex-core 添加代码！**

尤其在引入新概念、功能或 API 时，在添加到 `codex-core` 前，请考虑：

- 是否存在除 `codex-core` 之外更适合承载新代码的现有 crate。
- 是否到了为新功能在 Cargo workspace 中引入新 crate 的时候。必要时重构现有代码来实现这一点。

同样，在 review 代码时，不要犹豫，应推动拒绝那些会不必要地向 `codex-core` 添加代码的 PR。

## TUI style conventions

见 `codex-rs/tui/styles.md`。

## TUI code conventions

- 使用 ratatui 的 Stylize trait 提供的简洁 styling helpers。
  - 普通 spans：使用 `"text".into()`
  - 带样式 spans：使用 `"text".red()`、`"text".green()`、`"text".magenta()`、`"text".dim()` 等。
  - 优先使用这些方式，而不是直接构造 `Span::styled` 和 `Style`。
  - 示例：patch summary file lines
    - 推荐：`vec!["  └ ".into(), "M".red(), " ".dim(), "tui/src/app.rs".dim()]`

### TUI Styling（ratatui）

- 优先使用 Stylize helpers：尽量使用 `"text".dim()`、`.bold()`、`.cyan()`、`.italic()`、`.underlined()`，而不是手写 `Style`。
- 优先使用简单转换：span 使用 `"text".into()`，line 使用 `vec![…].into()`；当类型推断含糊时（例如 `Paragraph::new` / `Cell::from`），使用 `Line::from(spans)` 或 `Span::from(text)`。
- 计算得出的样式：如果 `Style` 是运行时计算出来的，可以使用 `Span::styled`（`Span::from(text).set_style(style)` 也可以）。
- 避免硬编码白色：不要使用 `.white()`；优先使用默认前景色（不设置颜色）。
- 链式调用：为了可读性，把 helpers 链起来使用，例如 `url.cyan().underlined()`。
- 单个 item：优先使用 `"text".into()`；只有当目标类型不明显，或使用 `.into()` 会需要额外类型注解时，才使用 `Line::from(text)` 或 `Span::from(text)`。
- 构建 lines：当目标类型明显且不需要额外类型注解时，使用 `vec![…].into()` 构造 `Line`；否则使用 `Line::from(vec![…])`。
- 避免无意义 churn：不要在等价形式之间来回重构（`Span::styled` ↔ `set_style`，`Line::from` ↔ `.into()`），除非有明确的可读性或功能收益；遵循文件本地约定，不要仅为满足 `.into()` 而引入类型注解。
- 紧凑性：优先选择 rustfmt 后仍能保持单行的形式；如果 `Line::from(vec![…])` 或 `vec![…].into()` 中只有一个能避免换行，就选那个。如果两者都会换行，选换行更少的形式。

### Text wrapping

- 始终使用 `textwrap::wrap` 包装普通字符串。
- 如果有 ratatui `Line` 并想换行，使用 `tui/src/wrapping.rs` 中的 helpers，例如 `word_wrap_lines` / `word_wrap_line`。
- 如果需要缩进换行后的 lines，尽可能使用 `RtOptions` 中的 `initial_indent` / `subsequent_indent` options，而不是自写逻辑。
- 如果有一组 lines，并需要给所有 lines 加 prefix（第一行和后续行可选不同 prefix），使用 `line_utils` 中的 `prefix_lines` helper。

## Tests

### Snapshot tests

该仓库使用 snapshot tests（通过 `insta`），尤其在 `codex-rs/tui` 中，用于验证渲染输出。

**要求：** 任何影响用户可见 UI 的变更（包括新增 UI）都必须包含对应的 `insta` snapshot coverage（如果没有现有 snapshot test，就添加新的；否则更新现有 snapshot）。作为 PR 的一部分 review 并接受 snapshot 更新，这样 UI 影响更容易 review，未来 diff 也保持可视化。

当 UI 或文本输出有意变化时，按如下步骤更新 snapshots：

- 运行测试生成更新后的 snapshots：
  - `just test -p codex-tui`
- 查看有哪些 pending：
  - `cargo insta pending-snapshots -p codex-tui`
- 通过直接阅读仓库中生成的 `*.snap.new` 文件 review 变化，或预览某个文件：
  - `cargo insta show -p codex-tui path/to/file.snap.new`
- 只有当你确实打算接受该 crate 中所有新 snapshots 时，才运行：
  - `cargo insta accept -p codex-tui`

如果没有该工具：

- `cargo install --locked cargo-insta`

### Test assertions

- 测试应使用 `pretty_assertions::assert_eq` 以获得更清晰的 diff。如果尚未导入，请在测试模块顶部导入。
- 只要可能，优先使用深度相等比较。对整个对象执行 `assert_eq!()`，而不是逐字段比较。
- 避免在测试中修改进程环境；优先从上层传入环境派生 flags 或 dependencies。

### 在测试中启动 workspace binaries（Cargo vs Bazel）

- 当测试需要启动 first-party binaries 时，优先使用 `codex_utils_cargo_bin::cargo_bin("...")`，而不是 `assert_cmd::Command::cargo_bin(...)` 或 `escargot`。
  - 在 Bazel 下，binaries 和 resources 可能位于 runfiles 中；使用 `codex_utils_cargo_bin::cargo_bin` 可解析出在 `chdir` 后仍稳定的绝对路径。
- 在 Bazel 下定位 fixture files 或 test resources 时，避免使用 `env!("CARGO_MANIFEST_DIR")`。优先使用 `codex_utils_cargo_bin::find_resource!`，让路径在 Cargo 和 Bazel runfiles 下都能正确解析。

### Integration tests（core）

- 写 end-to-end Codex 测试时，优先使用 `core_test_support::responses` 中的工具。

- 所有 `mount_sse*` helpers 都返回 `ResponseMock`；保留它，以便断言 outbound `/responses` POST bodies。
- 当测试应只发出一个 POST 时，使用 `ResponseMock::single_request()`；如果要检查所有捕获的 `ResponsesRequest`，使用 `ResponseMock::requests()`。
- `ResponsesRequest` 暴露 helpers（`body_json`、`input`、`function_call_output`、`custom_tool_call_output`、`call_output`、`header`、`path`、`query_param`），让断言能针对结构化 payload，而不是手动挖 JSON。
- 使用提供的 `ev_*` constructors 和 `sse(...)` 构建 SSE payloads。
- 优先使用 `wait_for_event`，而不是 `wait_for_event_with_timeout`。
- 优先使用 `mount_sse_once`，而不是 `mount_sse_once_match` 或 `mount_sse_sequence`。

典型模式：

```rust
let mock = responses::mount_sse_once(&server, responses::sse(vec![
    responses::ev_response_created("resp-1"),
    responses::ev_function_call(call_id, "shell", &serde_json::to_string(&args)?),
    responses::ev_completed("resp-1"),
])).await;

codex.submit(Op::UserTurn { ... }).await?;

// 如有需要，断言 request body。
let request = mock.single_request();
// 使用 request.function_call_output(call_id) 或 request.json_body() 等 helper 断言。
```

## App-server API Development Best Practices

这些指南适用于 `codex-rs` 中的 app-server protocol 工作，尤其是：

- `app-server-protocol/src/protocol/common.rs`
- `app-server-protocol/src/protocol/v2.rs`
- `app-server/README.md`

### Core Rules

- 所有活跃 API 开发都应发生在 app-server v2。不要向 v1 添加新的 API surface area。
- 保持 payload 命名一致：
  request payload 使用 `*Params`，response 使用 `*Response`，notification 使用 `*Notification`。
- RPC methods 暴露为 `<resource>/<method>`，并保持 `<resource>` 为单数（例如 `thread/read`、`app/list`）。
- 除非 tagged union 或显式兼容性要求需要 targeted rename，否则 wire 上始终用 `#[serde(rename_all = "camelCase")]` 暴露字段。
- 例外：config RPC payloads 预期使用 snake_case，以镜像 `config.toml` keys（见 `app-server-protocol/src/protocol/v2.rs` 中的 config read/write/list APIs）。
- v2 request/response/notification types 上始终设置 `#[ts(export_to = "v2/")]`，确保生成的 TypeScript 落到正确 namespace。
- v2 API payload fields 永远不要使用 `#[serde(skip_serializing_if = "Option::is_none")]`。
  例外：有意没有 params 的 client->server requests 可使用：
  `params: #[ts(type = "undefined")] #[serde(skip_serializing_if = "Option::is_none")] Option<()>`。
- 保持 Rust 和 TS wire renames 对齐。如果字段或 variant 使用 `#[serde(rename = "...")]`，请添加匹配的 `#[ts(rename = "...")]`。
- 对 discriminated unions，在两个 serializers 中都使用显式 tagging：
  `#[serde(tag = "type", ...)]` 和 `#[ts(tag = "type", ...)]`。
- API 边界优先使用普通 `String` IDs（如有需要，在内部做 UUID 解析/转换）。
- 时间戳应是整数 Unix seconds（`i64`），并命名为 `*_at`（例如 `created_at`、`updated_at`、`resets_at`）。
- 对实验性 API surface area：
  使用 `#[experimental("method/or/field")]`；当需要 field-level gating 时 derive `ExperimentalApi`；当只有某个 method 的部分 fields 是实验性时，在 `common.rs` 中使用 `inspect_params: true`。

### Client->server request payloads（`*Params`）

- 每个 optional field 都必须标注 `#[ts(optional = nullable)]`。不要在 client->server request payloads（`*Params`）以外使用 `#[ts(optional = nullable)]`。
- Optional collection fields（例如 `Vec`、`HashMap`）必须使用 `Option<...>` + `#[ts(optional = nullable)]`。不要用 `#[serde(default)]` 表示 optional collections，也不要在 v2 payload fields 上使用 `skip_serializing_if`。
- 当你希望 boolean field 被省略时表示 `false`，使用 `#[serde(default, skip_serializing_if = "std::ops::Not::not")] pub field: bool`，而不是 `Option<bool>`。
- 新 list methods 默认实现 cursor pagination：
  request fields 为 `pub cursor: Option<String>` 和 `pub limit: Option<u32>`，
  response fields 为 `pub data: Vec<...>` 和 `pub next_cursor: Option<String>`。

### Development Workflow

- API 行为变化时更新 app-server docs/examples（至少更新 `app-server/README.md`）。
- API shapes 变化时重新生成 schema fixtures：
  `just write-app-server-schema`
  （如果影响 experimental API fixtures，则运行 `just write-app-server-schema --experimental`）。
- 使用 `just test -p codex-app-server-protocol` 验证。
- 避免只断言 `common.rs` 中单个 request field experimental marker 的 boilerplate tests；改为依赖 schema generation/tests 和行为覆盖。

