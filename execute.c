#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * execute_command - Executes a shell command.
 * @command: The command to execute.
 * @argv0: The name of the executing program.
 */
void execute_command(char *command, char *argv0)
{
    pid_t pid, wpid;
    int status;
    char *args[64];
	int i = 0;

	args[i] = strtok(command, " \n");
	while (args[i] != NULL)
	{
		i++;
		args[i] = strtok(NULL, " \n");
	}
	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv0, args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		do
        {
			wpid = waitpid(pid, &status, WUNTRACED);
		}
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
