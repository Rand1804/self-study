# codex-shell-escalation

> 原文：`AI/codex/codex-rs/shell-escalation/README.md`

该 crate 包含 Unix shell-escalation protocol 实现和 `codex-execve-wrapper` 可执行文件。

`codex-execve-wrapper` 接收被拦截的 `execve(2)` 调用参数，并通过共享文件描述符上的 shell-escalation protocol 把决策委托给另一端 server。文件描述符由 `CODEX_ESCALATE_SOCKET` 环境变量指定。

server 返回三种结果之一：

- `Run`：`codex-execve-wrapper` 应对自身调用 `execve(2)`，在 sandboxed shell 中运行原命令。
- `Escalate`：转发当前进程的 file descriptors，使命令能在 sandbox 外保真运行。进程完成后，server 将 exit code 转回 `codex-execve-wrapper`。
- `Deny`：server 声明该命令 forbidden，`codex-execve-wrapper` 向 stderr 打印错误并以 `1` 退出。

## Patched zsh

仓库包含对 `Src/exec.c` 的小 patch（见 `patches/zsh-exec-wrapper.patch`），添加对 `EXEC_WRAPPER` 的支持。该 patch 适用于 zsh 源码中的指定 commit。手动重建流程见原文。
