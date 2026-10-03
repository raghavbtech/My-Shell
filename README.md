# myshell — A Simple Unix Shell in C

## Overview

`myshell` is a simplified command-line shell written in C, similar in spirit
to `bash`. It reads commands from the user, runs them as separate processes,
and supports a handful of built-in commands. This project was built to
understand how Unix shells work under the hood — specifically how process
creation (`fork`), program execution (`exec`), and process synchronization
(`wait`) work together.

## Goals

- Understand and implement the fork/exec/wait process model used by all
  Unix shells
- Build a shell that can run any external program available on the system
- Implement common built-in commands that cannot be handled as external
  processes (e.g. `cd`)
- Add quality-of-life features (history, variable expansion, command
  chaining) on top of the core shell

## Specifications and Design

The shell operates in a read-execute loop:

1. Print a prompt showing the current working directory
2. Read a line of input from the user
3. Split the line into separate commands on `;` (if present)
4. For each command: expand any `$VARIABLE` references, then check if it's
   a built-in; if not, `fork()` a child process and `execvp()` the command
   in it, while the parent `wait()`s for it to finish

### Architecture

The codebase is organized into modular components:

- **`src/shell.h`** — shared definitions, constants (`MAX_LINE`, `MAX_ARGS`, `MAX_HISTORY`), and declarations
- **`src/shell.c`** — main read-execute loop, `print_prompt()`, and `read_line()`
- **`src/parse.c`** — command tokenization (`parse_line()`) and environment variable expansion (`expand_variables()`)
- **`src/builtin.c`** — built-in commands (`cd`, `pwd`, `exit`, `help`, `clear`, `history`) and history management
- **`src/execute.c`** — process creation (`fork`, `execvp`, `waitpid`) and I/O redirection (`handle_redirection()`)

## Features

- Interactive prompt showing current directory
- Runs any external program available on the system (`ls`, `cat`, `pwd`, etc.)
- Built-in commands: `cd`, `pwd`, `exit`, `help`, `clear`, `history`
- Command history tracking
- Input and output redirection (`<`, `>`)
- Multiple commands per line, separated by `;`
- Environment variable expansion (e.g. `echo $HOME`) — read-only

## Known Limitations / Future Work

- No pipes (`|`) between commands
- No append redirection (`>>`)
- No background execution (`&`)
- No custom variable assignment (e.g. `name=value`) — only existing system
  environment variables can be read via `$VAR`
- No wildcard expansion (e.g. `*.c`)

These were intentionally left out of scope to keep the project focused.

## Prerequisites

- A Unix-like OS (Linux or macOS)
- `gcc` installed
- `make` installed

## Build Instructions

```bash
git clone <your-repo-url>
cd myshell
make
```

This compiles `src/shell.c` into an executable called `myshell`.

## Run Instructions

```bash
./myshell
```

## Example Usage
myshell:/home/user/myshell> pwd
/home/user/myshell
myshell:/home/user/myshell> ls -l
total 24
-rw-r--r-- 1 user user 512 Sep 25 10:00 shell.c
myshell:/home/user/myshell> echo $USER
user
myshell:/home/user/myshell> pwd ; whoami
/home/user/myshell
user
myshell:/home/user/myshell> history
1 pwd
2 ls -l
3 echo $USER
4 pwd ; whoami
myshell:/home/user/myshell> cd ..
myshell:/home/user> foobar
myshell: command not found: foobar
myshell:/home/user> exit


## Cleaning Up

```bash
make clean
```

Removes the compiled `myshell` binary.

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file.
Final folder structure
myshell/
├── src/
│   ├── shell.h
│   ├── shell.c
│   ├── parse.c
│   ├── builtin.c
│   └── execute.c
├── Makefile
├── README.md
├── LICENSE
└── .gitignore