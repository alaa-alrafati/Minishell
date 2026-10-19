*This project has been created as part of the 42 curriculum by hsbeh, aalrofat.*

<div align="center">
  <h1> Minishell 🐚🐧</h1>
  <p><i>A small Bash recreation built from scratch in C.</i></p>
</div>

---

## 📖 Description

**The Scenario:**
The terminal you use every day (like Bash) isn't magic; it's just a program written in C. It reads the text you type, understands the rules (like quotes and pipes), and asks the operating system to execute it.

A shell is simply a program that:
- reads the command typed by the user
- understands and parses the input
- creates processes
- executes commands
- manages pipes, redirections, and environment variables

**The Goal: Build our own little Bash!**
The goal of this project is to recreate the core behavior of a real UNIX shell and understand what happens behind the terminal we use every day. In this project, we built our own simplified Bash from scratch while focusing on low-level system programming and Unix process management.

**The Challenge:**
The main challenge was to correctly parse complex user input, handle multiple commands running at the same time, and safely manage file descriptors. We also had to ensure that parent and child processes communicate perfectly—all without a single memory leak.


## ⚙️ How Minishell Works

### 🔹 Lexing & Parsing
The shell reads the raw user input and transforms it into structured tokens such as:
- commands and arguments
- pipes (`|`)
- redirections (`<`, `>`, `>>`, `<<`)
while correctly handling single and double quotes.

### 🔹 Environment Expansion
Variables like `$USER` and `$?` are detected inside the input and expanded to their actual values before execution.

### 🔹 Command Execution
Commands are executed using low-level system calls such as `fork()`, `execve()`, `waitpid()`, and `pipe()`. This allows multiple processes to run and communicate exactly like in Bash.

### 🔹 Built-in Commands
Several Bash built-ins were recreated manually, including: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

---

## ✅ What We Learned

Beyond just executing commands, our main focus was building a stable, modular, and leak-free architecture. This project helped deepen our understanding of:

- **UNIX Internals:** Working directly with system calls, process creation, and file descriptors.
- **Signal Handling:** Making sure `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` behave exactly like they do in real Bash.
- **Memory & Resource Safety:** Strictly preventing memory leaks and open file descriptor (FD) leaks.
- **Stability & Edge Cases:** Parsing complex rules, quotes, and weird user inputs cleanly without crashing.
- **Process Coordination:** Managing parent and child processes smoothly across complex pipelines.

---
## Instructions (How to Run Minishell 🚀)

### Compilation
The project includes a `Makefile` to compile the source code cleanly. Run the following commands in your terminal:
* `make` - Compiles the project and generates the `minishell` executable.
* `make clean` - Removes the generated object files.
* `make fclean` - Removes object files and the executable.
* `make re` - Recompiles the entire project from scratch.

### 📋 Usage Instructions

Once compiled, you can start the shell by running:

```Bash
./minishell
```
This will launch the interactive prompt. From here, you can execute standard UNIX commands, test complex pipelines (|), and manage environment variables just like you would in Bash.

### Example Commands

```bash
echo Hello Minishell
pwd
ls -la
cat file.txt | grep hello
echo $USER
```

###  Exit the Shell

To safely close the shell, you can either type:
```bash
exit
```
or press:
```bash
Ctrl + D
```
---

## Resources & References
Useful resources that helped us build Minishell:

* **[GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html):** The official guide used to understand Bash parsing rules, quotes, and variable expansions.
* **[Introduction to Systems Programming (Chapter 5) - Purdue University](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf):** Explains the core logic behind parsing input and executing commands.
* **[Pipe: an Inter-Process Communication Method (by Mia Combeau)](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/):** Explains the core mechanics of inter-process communication, shell pipelines, and safe file descriptor management.

* **Linux Man Pages:** The primary reference used to implement and handle standard UNIX system calls and signals.

---

## 🤖 AI Usage Statement
Throughout this project, AI was utilized as an educational assistant and virtual mentor.

Here is exactly how AI was used, specifying the tasks and parts of the project:

* **Conceptual Clarification (Architecture & Execution):** Used AI to generate analogies and text-based diagrams to better understand the low-level flow of complex system calls, particularly how `pipe()` and `dup2()` interact across multiple child processes.
* **Advanced Debugging Assistant (Memory & Edge Cases):** We used AI to analyze and translate complex `Valgrind` logs. This helped us pinpoint where our file descriptors (FDs) were leaking in the execution pipeline without providing the direct code fixes.
* **Documentation (README):** AI was used as an editorial tool to polish the English grammar, structure, and Markdown formatting of this exact `README.md` file.
