#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\033[31m"
# define RESET "\033[0m"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h> // open
#include <wait.h> // wait, waitpid
#include <sys/stat.h>
#include <signal.h> // signal, kill
#include <errno.h> // errno
#include <term.h> // termcap
#include <dirent.h> // opendir
#include <string.h> // strerror

# endif