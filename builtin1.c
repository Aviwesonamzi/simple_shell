#include"shell.h"
/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: env var name
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *nde = info->env;
	char *ptr;

	while (nde)
	{
		ptr = starts_with(nde->ptr, name);
		if (ptr && *ptr)
			return (ptr);
		nde = nde->next;
	}
	return (NULL);
}

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove environment variable
 * @info: Structure containing potential arguments
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
	int e;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (e = 1; e <= info->argc; e++)
		_unsetenv(info, info->argv[e]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t e;

	for (e = 0; envi[e]; e++)
		add_node_end(&node, envi[e], 0);
	info->env = node;
	return (0);
}
