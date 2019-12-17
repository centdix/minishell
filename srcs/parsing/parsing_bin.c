/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:01:49 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 20:05:14 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If the path on line isn't /bin/, set it to /bin (working with binary ./)
*/

int		check_line(char **line, char **bin_paths, char **path)
{
	int		i;
	char	*tmp;
	char	*begin;

	i = -1;
	while (bin_paths[++i] && (begin = *line))
	{
		tmp = get_data_no_space(line);
		*line = begin;
		if (!ft_strcmp(tmp, bin_paths[i]))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
		if (!ft_strncmp(*line, bin_paths[i], ft_strlen(bin_paths[i]))
		|| !ft_strncmp(*line, "./", 2))
		{
			if (!(*path = get_data_no_space(line)))
				return (-2);
			break ;
		}
	}
	return (i);
}

char	*create_bin_path(char **line, t_minishell *minishell)
{
	char	*exec;
	char	*path;
	int		i;
	char	**bin_paths;

	bin_paths = minishell->bin_paths;
	i = check_line(line, bin_paths, &path);
	if (i < 0)
		return (NULL);
	if (bin_paths[i] == NULL)
	{
		if (!(exec = get_data_no_space(line)))
			return (NULL);
		if (!(path = find_path(exec, bin_paths)))
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
	{
		*line = begin;
		return (0);
	}
	if (path)
	{
		*line = begin;
		free(path);
		if ((add_back(&minishell->commands, TYPE_BIN, NULL,
		get_data_one_space(line)) < 0))
			return (-1);
		return (1);
	}
	*line = begin;
	return (0);
}
