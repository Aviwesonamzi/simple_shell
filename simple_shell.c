#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point for the simple shell.
 * Return: 0 on success, EXIT_FAILURE otherwise.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *args[2];
    pid_t pid, wpid;
    int status;

    while (1)
    {
        write(STDOUT_FILENO, "($) ", 4);
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin))
            {
                exit(EXIT_SUCCESS);
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }
        line[read - 1] = '\0';  /* Remove the newline character */

        /* Prepare the command for execve */
        args[0] = line;
        args[1] = NULL;

        /* Fork a new process */
        pid = fork();
        if (pid == 0)
        {
            /* Child process */
            if (execve(args[0], args, NULL) == -1)
            {
                fprintf(stderr, "%s: command not found\n", args[0]);
                exit(EXIT_FAILURE);
            }
        }
        else if (pid < 0)
        {
            /* Forking error */
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process */
            do
            {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    free(line);
    return (0);
}