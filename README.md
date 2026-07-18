# Minishell

Minishell is a small interactive Unix shell written in C as part of the 42
curriculum. It recreates the core journey of a shell command: reading input,
parsing it, expanding environment variables, connecting pipes and
redirections, launching programs, and collecting their exit status.

The goal is not to replace Bash, but to understand what happens between typing
a command and seeing its result.

## What it can do

- Display an interactive prompt with command history through GNU Readline
- Find and execute programs from `PATH` with `fork`, `execve`, and `wait`
- Run multiple commands connected by pipes (`|`)
- Handle input and output redirections:
  - `<` reads from a file
  - `>` writes to a file
  - `>>` appends to a file
  - `<<` reads a here-document until a delimiter
- Expand environment variables such as `$HOME`
- Expand `$?` to the most recent command's exit status
- Keep a private, mutable copy of the environment
- React to `Ctrl-C`, `Ctrl-\`, and end-of-file (`Ctrl-D`)
- Provide the required shell built-ins:
  - `echo`, including `-n`
  - `cd`, including `cd`, `cd ~`, and `cd -`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

Minishell implements a focused subset of shell behavior and should not be
treated as a fully Bash-compatible shell.

## How it was built

The project is divided into three main layers:

```text
Readline input
      |
      v
Expansion and parsing
  - environment variables and $?
  - quote-aware tokenization
  - pipelines
  - redirection lists
      |
      v
Command execution
  - built-ins in the shell process
  - PATH resolution
  - pipes and file descriptors
  - fork + execve
  - wait and exit status
```

### Parsing

The interactive loop in `parsing/loop.c` reads a line, stores it in Readline
history, performs variable expansion, normalizes redirection operators that
have no surrounding spaces, and creates a linked list of commands.

Each pipeline stage is represented by a `t_token`. It owns:

- the original command text;
- a null-terminated argument array for execution;
- a linked list of input/output redirections;
- a pointer to the next pipeline stage.

The parser recognizes separators while tracking quotes so that delimiters
inside quoted text are not treated like normal separators.

### Execution

`command.c` walks the command list and creates a pipe whenever another stage
follows. File redirections and pipe ends are connected to standard input or
standard output with `dup2`.

Built-ins are dispatched directly so commands that must change shell state,
such as `cd`, `export`, and `unset`, affect the current process. External
commands are resolved against the shell's copied `PATH`, executed in a child
process with `execve`, and reaped with `wait`.

The exit status of the last child is stored in the shell state and made
available through `$?`.

### Environment and memory

At startup, Minishell duplicates `envp` rather than modifying the parent
process's environment. Helper functions add, update, remove, copy, and free
null-terminated string arrays. `PATH` is split into a separate search array and
refreshed when it changes through `export` or `unset`.

The parser and executor explicitly release command arrays, token lists,
redirection nodes, environment copies, Readline state, and temporary strings.

### Project structure

```text
.
├── main.c                       # initialization and entry point
├── env.c                        # environment and PATH setup
├── builtins_first.c             # cd, echo, pwd, exit, dispatch
├── builtins_sec.c               # export, unset, env
├── command.c                    # pipelines, redirections, execution
├── command_utils*.c             # descriptors, heredoc, exec helpers
├── multidimensional*.c          # char ** environment utilities
├── parsing/                     # prompt, tokenizer, expansion, signals
├── 42_libft/                    # local C utility library
├── minishell.h                  # shared execution declarations
└── Makefile
```

The Makefile compiles with `-Wall -Wextra -Werror -g`, builds the bundled
`42_libft` static library, and links Minishell against GNU Readline.

## Run it locally

### Requirements

Minishell uses POSIX process and terminal APIs, so build it on Linux, macOS, or
inside a Linux environment such as WSL. You need:

- a C compiler (`cc`, GCC, or Clang);
- `make`;
- GNU Readline headers and library.

On Debian or Ubuntu:

```sh
sudo apt update
sudo apt install build-essential libreadline-dev
```

On macOS with Homebrew:

```sh
brew install readline
```

If Homebrew's Readline is not discovered automatically, provide its include and
library paths when building:

```sh
make CFLAGS="-Wall -Wextra -Werror -g -I$(brew --prefix readline)/include" \
     LDFLAGS="-L$(brew --prefix readline)/lib"
```

> Note: the current Makefile does not use `LDFLAGS`. On a macOS setup where
> Readline is not in the default linker path, add
> `-L$(brew --prefix readline)/lib` to the final link command in the Makefile.

### Build and start

```sh
git clone <repository-url>
cd minishell
make
./minishell
```

The program opens the `MINISHELL$$` prompt and does not accept command-line
arguments.

Example session:

```console
MINISHELL$$ echo "hello from minishell"
hello from minishell
MINISHELL$$ pwd
/path/to/minishell
MINISHELL$$ echo hello | wc -c
6
MINISHELL$$ echo "$HOME"
/home/user
MINISHELL$$ cat < input.txt | grep error > errors.txt
MINISHELL$$ exit
```

### Make targets

```sh
make          # build 42_libft and minishell
make clean    # remove object files
make fclean   # remove object files, libraries, and executable
make re       # perform a clean rebuild
```

### With Docker

Run locally:
```sh
  docker build -t minishell .
  docker run --rm -it minishell
```

## What I learned by building it

Building Minishell turned isolated C concepts into one stateful systems
program. In particular, I learned:

- **Process creation and control.** I learned how `fork` creates a second
  process, how `execve` replaces the child image, and how `wait`/`waitpid`
  communicate completion and exit codes back to the shell.
- **File descriptors are a universal interface.** Pipes, files, standard input,
  and standard output can all be connected by carefully duplicating and
  closing descriptors with `dup`, `dup2`, and `close`.
- **Parsing needs state.** Even a small shell grammar must distinguish quoted
  text, whitespace, pipeline separators, redirection operators, and variable
  names. A character's meaning depends on its context.
- **Shell state belongs to the parent process.** Running `cd`, `export`, or
  `unset` only in a child would lose the change as soon as that child exits.
  State-changing built-ins therefore need special handling.
- **Signals are part of interactive program design.** `Ctrl-C` at an idle
  prompt, during a child command, and inside a here-document are related events
  but require different behavior.
- **Ownership must be explicit in C.** Token lists, argument arrays,
  redirection nodes, environment strings, and temporary expansions all need a
  clear owner and cleanup path.
- **Errors cross process boundaries.** A failed `open`, `pipe`, `fork`, or
  `execve` must be reported from the correct process while leaving descriptors
  and allocated memory in a valid state.
- **Modular design matters.** Separating parsing, execution, built-ins,
  environment management, signals, and utility code made a complex control flow
  easier to reason about and debug.

More broadly, the project taught me that a familiar interface can hide a large
amount of operating-system machinery. Rebuilding a small part of a shell made
processes, descriptors, signals, memory, and parsing feel concrete rather than
abstract.
