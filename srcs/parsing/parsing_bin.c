/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:01:49 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 03:42:53 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If the path on line isn't /bin/, set it to /bin
*/

char	*create_bin_path(char **line)
{
	char	*exec;
	char	*path;

	if (ft_strncmp(*line, "/bin/", 5))
	{
		if (!(exec = get_data_no_space(line)))
			return (NULL);
		if (!(path = ft_strjoin("/bin/", exec)))
		{
			free(exec);
			return (NULL);
		}
		free(exec);
	}
	else if (!(path = get_data_no_space(line)))
		return (NULL);
	return (path);
}

/*
** Parse a bin command
** return - 1 - bin found
** return - 0 - bin not found
** otherwise error
*/

int		parsing_bin(char **line, t_lstcommands **commands)
{
	void	*stat;
	char	*begin;
	char	*path;

	begin = *line;
	if (!(path = create_bin_path(line)))
		return (-1);
	if (!(stat = malloc(sizeof(struct stat))))
		return (-1);
	if (!lstat(path, stat))
	{
		ft_multifree(stat, path, NULL, NULL);
		*line = begin;
		if ((add_back(commands, TYPE_BIN, get_data_one_space(line))) < 0)
			return (-1);
		return (1);
	}
	*line = begin;
	ft_multifree(stat, path, NULL, NULL);
	return (0);
}
