# Minishell 🐌

Welcome to the 42 Minishell project! This project is part of the 42 curriculum, aimed at creating a simple shell that can interpret and execute commands. It is an educational project that helps students understand how a Unix-like shell works.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Examples](#examples)
- [Contributing](#contributing)


## Introduction

The 42 Minishell project is a small, simple shell that supports basic command execution, input/output redirection, pipes, and a few built-in commands. It is designed to provide a deeper understanding of how a shell works internally, including process creation, signal handling, and command parsing.

## Features

- Command execution (with arguments)
- Input/output redirection (`>`, `<`, `>>`, `<<`)
- Pipes (`|`)
- Environment variable handling
- Built-in commands (e.g., `cd`, `echo`, `exit`, etc.)
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`)

## Installation

To install and compile the Minishell, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/BorisMichaelRandebrock/minishell.git
   cd minishell

2. Compile the project:
   ```sh
   make
   ```

3. Run the Minishell:
   ```sh
   ./minishell
   ```

## Usage

Once you have compiled and run the Minishell, you can start typing commands just like you would in a regular Unix shell. Here are some basic usage examples:

```sh
# Running a simple command
ls -la

# Using pipes
cat file.txt | grep "search_term"

# Redirecting output
echo "Hello, World!" > output.txt

# Redirecting input
cat < input.txt

# Using built-in commands
cd /path/to/directory
echo "This is a test"
exit
```

## Built-in Commands

The following built-in commands are implemented in the Minishell:

- `cd [directory]`: Change the current directory.
- `echo [string ...]`: Print strings to the standard output.
- `exit [status]`: Exit the shell with an optional exit status.
- `env`: Display the environment variables.
- `setenv [variable] [value]`: Set or update an environment variable.
- `unsetenv [variable]`: Remove an environment variable.

## Examples

Here are a few examples of how to use the Minishell:

```sh
# List files in the current directory
minishell$ ls -la

# Change directory
minishell$ cd /home/user

# Print working directory
minishell$ pwd

# Create a new file and write to it
minishell$ echo "Hello, Minishell!" > hello.txt

# Display the contents of the file
minishell$ cat hello.txt

# Use a pipe to filter output
minishell$ ls -la | grep ".txt"

# Exit the shell
minishell$ exit
```

## Contributing

Contributions are welcome! If you would like to contribute to this project, please fork the repository and create a pull request with your changes. Make sure to follow the coding standards and include relevant tests with your contributions.

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes.
4. Push to your branch.
5. Create a pull request.


