# `apply_patch`

> 原文：`AI/codex/codex-rs/apply-patch/apply_patch_tool_instructions.md`

使用 `apply_patch` shell 命令编辑文件。

Patch 语言是精简的、面向文件的 diff 格式，便于解析且安全应用。整体结构：

```text
*** Begin Patch
[一个或多个文件段]
*** End Patch
```

每个文件操作必须带 header，动作有三种：

- `*** Add File: <path>`：创建新文件。后续每行都必须是 `+` 行。
- `*** Delete File: <path>`：删除已有文件。后面没有内容。
- `*** Update File: <path>`：原地 patch 已有文件，可选重命名。

`Update File` 后可紧跟：

```text
*** Move to: <new path>
```

表示重命名文件。随后是一个或多个 hunks，每个 hunk 用 `@@` 开始。Hunk 内每行以空格、`-` 或 `+` 开头。

上下文规则：

- 默认在每处修改上下各提供 3 行上下文。
- 如果上下文不足以唯一定位代码片段，可在 `@@` 后写类名或函数名。
- 如果代码块重复很多，可使用多个 `@@` 逐步定位到正确上下文。

完整 grammar：

```text
Patch := Begin { FileOp } End
Begin := "*** Begin Patch" NEWLINE
End := "*** End Patch" NEWLINE
FileOp := AddFile | DeleteFile | UpdateFile
AddFile := "*** Add File: " path NEWLINE { "+" line NEWLINE }
DeleteFile := "*** Delete File: " path NEWLINE
UpdateFile := "*** Update File: " path NEWLINE [ MoveTo ] { Hunk }
MoveTo := "*** Move to: " newPath NEWLINE
Hunk := "@@" [ header ] NEWLINE { HunkLine } [ "*** End of File" NEWLINE ]
HunkLine := (" " | "-" | "+") text NEWLINE
```

示例：

```text
*** Begin Patch
*** Add File: hello.txt
+Hello world
*** Update File: src/app.py
*** Move to: src/main.py
@@ def greet():
-print("Hi")
+print("Hello, world!")
*** Delete File: obsolete.txt
*** End Patch
```

注意：

- 必须包含 Add/Delete/Update header。
- 创建新文件时，每个新行也必须以 `+` 开头。
- 文件引用只能是相对路径，绝不能是绝对路径。
