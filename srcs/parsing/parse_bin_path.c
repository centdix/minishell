/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bin_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:44:17 by fgoulama          #+#    #+#             */
/*   Updated: 2019/12/17 20:08:15 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_bin_path(int count, char *path, char **bin_paths)
{
	int		j;
	int		i;
	char	*tmp;

	j = -1;
	while (++j < count && !(i = 0))
	{
		while (path[i] && path[i] != ':')
			i++;
		tmp = ft_substr(path, 0, i);
		bin_paths[j] = ft_strjoin(tmp, "/");
		free(tmp);
		path = ft_strchr(path, ':');
		path++;
	}
	bin_paths[j] = NULL;
}

int		parse_bin_path(t_minishell *minishell)
{
	char	*path;
	int		count;
	int		j;

	path = get_env_value(minishell->env_variables, "PATH");
	count = 1;
	j = 0;
	while (path[j])
		if (path[j++] == ':')
			count++;
	if (!(minishell->bin_paths = malloc(sizeof(char *) * count + 1)))
		return (-1);
	fill_bin_path(count, path, minishell->bin_paths);
	return (0);
}
