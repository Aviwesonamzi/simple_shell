#include"shell.h"
/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments
 *  Return: 1 or 0
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

int _setenv(info_t *info, char *var, char *value)
{
	char *ptr = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	ptr = malloc(_strlen(var) + _strlen(value) + 2);
	if (!ptr)
		return (1);
	_strcpy(ptr, var);
	_strcat(ptr, "=");
	_strcat(ptr, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = ptr;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), ptr, 0);
	free(ptr);
	info->env_changed = 1;
	return (0);
}
