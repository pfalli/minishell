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

'FORK'

Creating a child process using fork() is a common pattern in Unix-like operating systems for several reasons, particularly when you want to execute a new program within a process. Here's why and how it works:

Why Create a Child Process?
Isolation: Child processes are executed in a separate memory space. This isolation prevents the child process from affecting the parent process's memory and resources directly. If a child process encounters an error or crashes, it doesn't directly impact the parent process or other child processes.

Concurrency: By creating child processes, a program can perform multiple tasks concurrently. This is especially useful for servers and applications that need to handle multiple requests or tasks at the same time.

Executing New Programs: In Unix-like systems, creating a child process is a prerequisite for executing a new program within a process. The fork() system call creates a new process, and then exec() family functions (like execve() in your code) replace the child process's memory space with a new program. This pattern allows the parent process to continue running and possibly manage multiple child processes.

How Does the Child Process Work?
Creation: When fork() is called, the operating system creates a new process. This new process is nearly identical to the calling (parent) process. Both processes continue executing from the point where fork() was called, but they can differentiate their behavior based on the return value of fork().

Return Value of fork():

In the parent process, fork() returns the Process ID (PID) of the newly created child process.
In the child process, fork() returns 0.
If fork() fails, it returns -1 in the parent process.
Executing a New Program: In the child process (where fork() returned 0), you typically use an exec() family function (like execve() in your example) to replace the child process's memory space with a new program. The execve() function loads the binary executable specified in its first argument, passing the command-line arguments and environment variables provided.

Independence: Once execve() is successfully called in the child process, the original program in the child process is completely replaced by the new program. The child process then executes independently of the parent process, although it can communicate with the parent or other processes through inter-process communication mechanisms if needed.

Termination and Cleanup: When a child process finishes execution, it becomes a "zombie" process until its parent process retrieves its exit status (usually using wait() or waitpid()). This step is crucial for properly cleaning up system resources.

In summary, creating a child process allows a program to perform multiple tasks simultaneously, execute new programs, and ensure isolation between different tasks or services.



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