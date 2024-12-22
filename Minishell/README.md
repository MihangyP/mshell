# Minishell

## Description
Minishell is a project from 42 school that involves creating a simplified version of a Unix
shell. The goal of this project is to gain a deep understanding of how a shell works, particularly
in areas like process management, pipes, signals, and redirections.

## Features
- Execution of simple commands like `/bin/ls`.
- Support for one operator: |.
- Handling input and output redirections (`<`, `>`, `>>`).
- Support for heredoc (`<<`).
- Handling pipes (`|`) to connect multiple commands.
- Management of environment variables and their expansion (`$VAR`).
- Implementation of some built-in commands (`cd`, `echo`, `env`, `export`, `unset`, `exit`, `pwd`).
- Signal handling (notably `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`).

## Installation
To clone this repository and compile the project, follow the instructions below:

```bash
git clone https://github.com/DevAina/Minishell.git
cd minishell
make
```
## Utilisation
Après compilation, vous pouvez lancer le shell avec la commande suivante:
```bash
git clone https://github.com/DevAina/Minishell.git
cd minishell
make
```

## Usage
After compilation, you can run the shell with the following command:
```bash
./minishell
```

Some usage examples:
- Simple command: `ls`
- Output redirection: `echo "Hello" > file.txt`
- Pipe between two commands: `ls | grep minishell`
- Use of environment variables: `echo $HOME`

## Internal Working
### Parsing and Execution
1. **Lexing & Parsing**: The entered commands are analyzed and transformed
2. into an internal data structure.
3. **Execution**: The program handles process creation using `fork`, `execve`, and waits for each
4. command to finish with `waitpid`.

### Handling Redirections
Redirections are managed at execution time by closing and redirecting file descriptors. Except
for heredoc `<<`, which is always processed first.

### Handling Pipes
Pipes are handled using the system calls `pipe()` and `dup2()` to redirect the output of one
command to the input of the next.

### Signal Handling
- `Ctrl+C`: Interrupts the current process without closing the shell.
- `Ctrl+D`: Sends an EOF signal, which closes the shell.
- `Ctrl+\`: Ignores this signal to prevent exiting the shell with a `Quit (core dumped)`
message.

## Built-in Commands
- **`cd [dir]`**: Changes the current directory.
- **`echo [args]`**: Displays arguments, with support for the `-n` option to omit the newline.
- **`env`**: Displays environment variables.
- **`export [var=value]`**: Sets an environment variable.
- **`unset [var]`**: Removes an environment variable.
- **`exit [status]`**: Exits the shell with the given exit code.

## Structures
```
.
├── built_in # Built-in commands
├── includes
├── libft/ # Utility functions from libft
├── srcs/ # Folder containing source files
├── Makefile
└── README.md # This file
```

## Author(s)
- [Tolotriniavo RARIJAMIADANA](mailto:ainatolotriniavo7@gmail.com)
- [Tanjona RAVELOARIMANANA](mailto:tanjonarav@gmail.com)
