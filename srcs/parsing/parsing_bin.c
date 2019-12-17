/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:01:49 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 05:18:22 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If the path on line isn't /bin/, set it to /bin (working with binary ./)
*/
char	*find_path(char *exec, t_minishell *minishell)
{
	char	*full_path;
	int		i;
	void	*stat;

	if (!(stat = malloc(sizeof(struct stat))))
		return (NULL);
	i = 0;
	full_path = NULL;
	while (minishell->bin_paths[i])
	{
		if (full_path)
			free(full_path);
		full_path = ft_strjoin(minishell->bin_paths[i], exec);
		if (!lstat(full_path, stat))
		{
			free(exec);
			return (full_path);
		}
		i++;
	}
	free(exec);
	free(full_path);
	free(stat);
	return (NULL);
}

char	*create_bin_path(char **line, t_minishell *minishell)
{
	char	*exec;
	char	*path;
	int		i;
	char	**bin_paths;

	bin_paths = minishell->bin_paths;
	i = 0;
	while (bin_paths[i])
	{
		if (!ft_strncmp(*line, bin_paths[i], ft_strlen(bin_paths[i])) || !ft_strncmp(*line, "./", 2))
		{
			if (!(path = get_data_no_space(line)))
				return (NULL);
			break;
		}
		i++;
	}
	if (bin_paths[i] == NULL)
	{
		if (!(exec = get_data_no_space(line)))
			return (NULL);
		if (!(path = find_path(exec, minishell)))
			return (NULL);
	}
	return (path);
}

/*
** Parse a bin command
** return - 1 - bin found
** return - 0 - bin not found
** otherwise error
*/

int		parsing_bin(char **line, t_minishell *minishell)
{
	char	*begin;
	char	*path;

	begin = *line;
	if (!(path = create_bin_path(line, minishell)))
		return (-1);
	if (path)
	{
		*line = begin;
		free(path);
		if ((add_back(&minishell->commands, TYPE_BIN, NULL, get_data_one_space(line)) < 0))
			return (-1);
		//printf("%s\n", path);
		return (1);
	}
	*line = begin;
	//printf("%s\n", path);
	return (0);
}