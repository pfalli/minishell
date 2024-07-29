!Structure of t_ast Node (Including Pipes)

t_ast
+-------------------+
| node_type         |  -> NODE_CMD or NODE_PIPE
|                   |
| value             |  -> char **value (array of strings, only for NODE_CMD)
|  +------------+   |     +---------------------+
|  | value[0]   |----->   | "command"            |
|  +------------+   |     +---------------------+
|  | value[1]   |----->   | "arg1"               |
|  +------------+   |     +---------------------+
|  | value[2]   |----->   | "arg2"               |
|  +------------+   |     +---------------------+
|  | ...        |   |
|  +------------+   |
|                   |
| redir_list        |  -> List of redirection nodes (only for NODE_CMD)
|  +------------+   |     +---------------------+
|  | redir[0]   |----->   | redirection node     |
|  +------------+   |     +---------------------+
|  | redir[1]   |----->   | redirection node     |
|  +------------+   |     +---------------------+
|  | ...        |   |
|  +------------+   |
|                   |
| left              |  -> t_ast * (left child, for pipes)
| right             |  -> t_ast * (right child, for pipes)
+-------------------+

!Example Token List and AST Node Creation with Pipes

Assume a pipeline command like:

echo arg1 | grep arg2 > output.txt


!Resulting AST Structure


                            t_ast (pipe)
                            +-------------------+
                            | node_type         |  -> NODE_PIPE
                            | left              |  -> t_ast (echo command)
                            | right             |  -> t_ast (grep command)
                            +-------------------+
                        /                           \
     LEFT child (echo command)                     RIGHT child (grep command)
+-------------------+                           +-------------------+
| node_type         |  -> NODE_CMD              | node_type         |  -> NODE_CMD
| value             |  -> char **value          | value             |  -> char **value
|  +------------+   |     +------------+        |  +------------+   |     +---------------------+
|  | value[0]   |----->   | "echo"     |        |  | value[0]   |----->   | "grep"              |
|  +------------+   |     +------------+        |  +------------+   |     +---------------------+
|  | value[1]   |----->   | "arg1"     |        |  | value[1]   |----->   | "arg2"              |
|  +------------+   |     +------------+        |  +------------+   |     +---------------------+
|  | ...        |   |                           |  | ...        |   |
|  +------------+   |                           |  +------------+   |
| redir_list        |  -> NULL                  | redir_list        |  -> List of redirection nodes
+-------------------+                           |  +------------+   |     +---------------------+
                                                |  | redir[0]   |----->   | redirection node     |
                                                |  +------------+         | token_type = TOKEN_REDIR |
                                                +-------------------+     | value = ">"            |
                                                                          | target = "output.txt"  |
                                                                          +---------------------

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------



We are required to build a mini shell (command-line interpreter) that mimics the bash, hence the name it wouldn’t be doing all the work that bash does, but the basic functionality:

    The shell will work only in interactive mode (no scripts, i.e. the executable takes no arguments)
    Run simple commands with absolute, relative path (e.g. /bin/ls, ../bin/ls)
    Run simple commands without a path (e.g. ls, cat, grep, etc…)
    Have a working history (you can navigate through commands with up/down arrows)
    Implement pipes (|)
    Implement redirections (<, >, >>)
    Implement the here-doc (<<)
    Handle double quotes ("") and single quotes (''), which should escape special characters, beside $ for double quotes.
    Handle environment variables ($ followed by a sequence of characters).
    Handle signals like in bash (ctrl + C, ctrl + \, ctrl + D).
    Implement the following built-ins:
    — echo (option -n only)
    — exit
    — env (with no options or arguments)
    — export (with no options)
    — unset (with no options)
    — cd
    — pwd
    And for the bonus part (optional, but i did it, because it’s cool!)
    — handle && and || with the parenthesis () for priority.
    — handle * wildcards for the current working directory.

---------------------------------------------------------------------------------------------------------------------------

'ENVP'

char *envp[]: This is an array of strings representing the environment variables available to the program at the time of execution. Each string is in the form of key=value. This parameter is not as commonly used as argc and argv, and it's not part of the standard definition of main in ISO C. However, it's supported by some operating systems (like UNIX and UNIX-like systems) as a way to pass the entire environment of the program. This can be useful for programs that need to access environment variables without using other environment-access functions like getenv.

Using int main(int argc, char *argv[], char *envp[]) allows a program to receive and use command-line arguments and environment variables, providing flexibility for various applications, from simple command-line tools to complex applications that need to interact with the operating system's environment.

An environment variable is a dynamic-named value that can affect the way running processes will behave on a computer. They are part of the environment in which a process runs. For example, an environment variable can store information such as the user's home directory, the path to executable files, or the system locale and character encoding. These variables are passed from the parent process to the child process, thus establishing a user session's context.

In the context of the provided C code snippet, char *envp[] represents an array of strings, where each string is an environment variable passed to the program. Each environment variable is typically in the form of KEY=value. For example, PATH=/usr/bin:/bin is an environment variable that specifies the directories in which executable programs are located.

Here's a brief overview of how environment variables are used in programs:

Accessing Environment Variables: In C, environment variables can be accessed using the envp parameter of the main function, or through functions like getenv() and setenv().

Common Uses: Environment variables are commonly used for:

Configuring system settings (e.g., PATH, HOME, LANG).
Passing configuration options to applications.
Controlling the behavior of libraries and runtime environments.
Security Considerations: Since environment variables can influence the behavior of programs, they should be handled carefully, especially when dealing with untrusted input, to avoid security vulnerabilities such as command injection or privilege escalation.


--------------------------------------------------------------------------------------------------------------------------------------------

PSEUDOCODE

1. Read Input: You already have this step where you read the command using fgets.
2. Trim Input: Remove newline character from the input, which you also have done.
3. Tokenize Input: Split the command into tokens based on spaces or other delimiters to identify the command and its arguments.
4. Identify Command: Check if the first token is a recognized command.
5. Handle Command:
    - If it's a recognized command (like "ls"), proceed as you have by forking a new process and using execve to execute the command.
    - If it's not recognized, you can print an error message or handle it as you see fit.
6. Execute Command: For recognized commands, use the appropriate system call (execve in the case of "ls") to execute the command.
7. Wait for Command to Complete: For commands that create a child process, wait for the process to complete.


------------------------------------------------------------------------------------------------------------------------------------------------

step_by_step

    Prompt implementation
    HashTable functions implementation
    Tokenizer implementation
    Variables expansion implementation
    Builtins implementation
    Parse and execute sistem design
    Signals implementation
    Parsing implementation
    Execute implementation
    Norme
    Bugs hunting

![alt text](LRParser.png)
