#include "minishell.h"

int		parse_bin_path(t_minishell *minishell)
{
	char	*path;
	int		count;
	int		i;
	int		j;

	path = get_env_value(minishell->env_variables, "PATH");
	count = 1;
	j = 0;
	while (path[j])
		if (path[j++] == ':')
			count++;
	if (!(minishell->bin_paths = malloc(sizeof(char *) * count + 1)))
		return (-1);
	j = -1;
	while (++j < count && !(i = 0))
	{
		while (path[i] && path[i] != ':')
			i++;
		minishell->bin_paths[j] = ft_substr(path, 0, i);
		path = ft_strchr(path, ':');
		path++;
	}
	minishell->bin_paths[j] = NULL;
	return (0);
}