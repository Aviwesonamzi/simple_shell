#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - Entry point for the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success, EXIT_FAILURE otherwise.
 */
int main(int argc, char *argv[]) {
    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    (void)argc;
    while (1)
    {
		write(STDOUT_FILENO, "($) ", 4);
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		execute_command(line, argv[0]);
	}
	free(line);
	return (0);
}