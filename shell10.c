#include"shell.h"
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *ptr, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	ptr = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!ptr)
		return (NULL);
	ptr[0] = 0;
	_strcpy(ptr, dir);
	_strcat(ptr, "/");
	_strcat(ptr, HIST_FILE);
	return (ptr);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 or -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: 0
 */
int read_history(info_t *info)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *ptr = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	ptr = malloc(sizeof(char) * (fsize + 1));
	if (!ptr)
		return (0);
	rdlen = read(fd, ptr, fsize);
	ptr[fsize] = 0;
	if (rdlen <= 0)
		return (free(ptr), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (ptr[a] == '\n')
		{
			ptr[a] = 0;
			build_history_list(info, ptr + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(info, ptr + last, linecount++);
	free(ptr);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
