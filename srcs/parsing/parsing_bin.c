/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:01:49 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 09:44:35 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*exec;
	char	*path;

	begin = *line;
	if (ft_strncmp(*line, "/bin/", 5))
	{
		exec = get_data_no_space(line);
		path = ft_strjoin("/bin/", exec);
		free(exec);
	}
	else
		path = get_data_no_space(line);
	if (!(stat = malloc(sizeof(struct stat))))
		return (-1);
	if (!lstat(path, stat))
	{
		free(stat);
		free(path);
		*line = begin;
		if ((add_back(commands, TYPE_BIN, get_data_one_space(line))) < 0)
			return (-1);
		return (1);
	}
	*line = begin;
	free(stat);
	free(path);
	return (0);
}
