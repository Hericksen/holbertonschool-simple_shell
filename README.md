# Simple Shell

## 📜 Description
**Simple Shell** is a basic UNIX command-line interpreter built as part of the Holberton School curriculum.
It emulates a simple shell environment and supports basic commands and utilities to give insight into the inner workings of a shell.

---

## ✍️ Flowchart

[![Flowchart-shell.png](https://i.postimg.cc/L694Q0zB/Flowchart-shell.png)](https://postimg.cc/RqYzNdpN)

---
## 🚀 Features
- **Interactive Mode**: Displays a prompt (`$`) and executes commands entered by the user.
- **Non-Interactive Mode**: Reads and executes commands from a file or pipeline.
- Executes commands using the system's `PATH`.
- Handles errors gracefully for unknown commands or missing executables.
- Built-in commands:
  - `exit`: Exits the shell.
  - `env`: Prints the current environment variables.

---

## 📋 Requirements
- **Operating System**: Linux or any UNIX-like environment.
- **Compiler**: GCC with flags: `-Wall -Werror -Wextra -pedantic`.

---

## 🔧 Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Hericksen/holbertonschool-simple_shell.git

## 💾 Example

Example of error with sh:
   ```bash
   $ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with our program hsh:
   ```bash
   $ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
## 👨🏽‍💻 Authors

Gwendal Martin | https://github.com/Hericksen

Jean-Alain Renié | https://github.com/JaRenie-spec


