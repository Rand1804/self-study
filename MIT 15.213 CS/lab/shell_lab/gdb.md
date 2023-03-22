```bash
# gdb


exec-file tsh
file tsh

run
step
next
continue
finish
break sigchld_handler
info break
disable 1
enable 1
delete 1
watch 3
info watch

list sigchld_handler

signal SIGINT
frame

show detach-on-fork
set detach-on-fork off

info inferiors
inferior 2
info proc
detach inferior 2

call fgpid(jobs)
catch fork
```

