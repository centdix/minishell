/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect_double_output.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 03:04:55 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 18:27:44 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check error for redirect_double_output
*/

int		check_error_double_output(char **data, char **name, char **line,
char **begin)
{
	int		ret;
	void	*stat;

	if (!(stat = malloc(sizeof(struct stat))))
		return (-1);
	if (opendir(*data) || (!lstat(*data, stat) &&
(ret = open(*data, O_RDONLY)) < 0))
	{
		*line = *begin;
		*line = &(*line)[2];
		if (opendir(*data))
		{
			ft_multifree(*data, *name, stat, NULL);
			return (IS_A_DIRECTORY);
		}
		ft_multifree(*data, *name, stat, NULL);
		return (PERM_DENIED);
	}
	free(stat);
	return (0);
}

/*
** Parsing >> (redirect double output)
*/

int		parsing_redirect_double_output(char **line, t_lstcommands **commands)
{
	int		ret;
	char	*begin;
	char	*name;
	char	*data;

	begin = (*line);
	*line = &(*line)[2];
	if ((check_too_many_args(line, 1)) < 0)
		return (TOO_MANY_ARGS);
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if (!(data = get_data_no_space(line)))
		return (-1);
	if ((ret = check_error_double_output(&data, &name, line, &begin)) < 0)
		return (ret);
	if ((add_back(commands, TYPE_RD_DB_OUT, name, data) < 0))
		return (-1);
	return (1);
}
