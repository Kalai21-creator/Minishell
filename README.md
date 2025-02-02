# Mini-Shell (msh)

## Overview

`mini-shell (msh)` is a minimalistic shell implemented as part of the Linux Internal module. The objective of this project is to gain hands-on experience with system calls related to process creation, signal handling, process synchronization, exit status management, and text parsing.

## Objective

The primary goal of `msh` is to provide a functional command-line environment where users can:

- Enter and execute commands
- Handle background and foreground processes
- Customize the shell prompt
- Handle signals effectively
- Use built-in commands and job control functionalities

---

## Features

### 1. Command Prompt

- Displays a default prompt: `msh>`
- Allows customization of the prompt using the `PS1` environment variable.
  - Usage: `PS1=NEW_PROMPT`
  - **Note:** Whitespace between `=` is not allowed; for example, `PS1 = NEW_PROMPT` should be treated as a normal command.

### 2. Command Execution

- Users can enter commands to execute.
- **External Commands:**
  - Creates a child process to execute the command.
  - Parent waits for the child to complete before showing the prompt again.
  - If the user presses enter without a command, the prompt is redisplayed.

### 3. Special Variables

- **Exit Status:**
  - Usage: `echo $?`
  - Prints the exit status of the last executed command.
- **Shell PID:**
  - Usage: `echo $$`
  - Displays the PID of the current shell instance.
- **Shell Name:**
  - Usage: `echo $SHELL`
  - Prints the executable path of `msh`.

### 4. Signal Handling

- **Ctrl-C (SIGINT):**
  - If a program is running in the foreground, sends `SIGINT` to the child process.
  - If no foreground program exists, redisplays the prompt.
- **Ctrl-Z (SIGTSTP):**
  - Stops the foreground program and displays the PID of the child.

### 5. Built-in Commands

- **exit:** Terminates the `msh` program.
- **cd:** Changes the current directory.
- **pwd:** Displays the current working directory.

### 6. Background Process / Job Control

- **Background Execution:**
  - Use `&` after a command to run it in the background. Example: `sleep 50 &`
- **Built-in Commands:**
  - `bg`: Moves a stopped process to the background.
  - `fg`: Brings a background process to the foreground. Brings either the last background process or a given PID to the foreground.
  - `jobs`: Displays details of all background processes.
- **Background Process Cleanup:**
  - On termination of a background process, cleans up the process using a `SIGCHLD` signal handler and displays its exit status.

### 7. Pipe Functionality

- Enables communication between multiple processes using pipes.
- Dynamically creates pipes and child processes based on the command-line input.
  - Example: `ls | wc` or `ls -l /dev | grep tty | wc -l`

---

## How to Use

1. **Compile:**
   ```bash
   gcc -o msh msh.c
   ```
2. **Run the Shell:**
   ```bash
   ./msh
   ```
3. **Execute Commands:**
   - Enter commands as you would in a standard shell.
   - Use built-in commands and background process management.

---

## Example Usage

```bash
msh> pwd
/home/user
msh> PS1=custom_prompt>
custom_prompt> echo $$
12345
custom_prompt> sleep 10 &
custom_prompt> jobs
[1] Running    sleep 10 &
custom_prompt> fg 1
```

---

## Notes

- Ensure proper handling of errors and invalid input.
- Use appropriate system calls for process management and signal handling.
- Keep the shell lightweight and responsive.

