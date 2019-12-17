/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 03:06:32 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 17:44:04 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_redirect_input_error(char **begin, char **line,
char **data, char **name)
{
	int		ret;
	void	*stat;

	if (!(stat = malloc(sizeof(struct stat))))
		return (-1);
	if ((ret = lstat(*data, stat)))
	{
		*line = *begin;
		(*line)++;
		ft_multifree(stat, *data, *name, NULL);
		return (NO_SUCH_FILE);
	}
	free(stat);
	if ((ret = open(*data, O_RDONLY)) < 0 && !(opendir(*data)))
	{
		*line = *begin;
		(*line)++;
		ft_multifree(*data, *name, NULL, NULL);
		return (PERM_DENIED);
	}
	close(ret);
	return (0);
}

/*
** Parsing < (redirect_input)
*/

int		parsing_redirect_input(char **line, t_lstcommands **commands)
{
	int		ret;
	char	*begin;
	char	*name;
	char	*data;

	begin = (*line)++;
	if ((check_too_many_args(line, 1)) < 0)
		return (TOO_MANY_ARGS);
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if (!(data = get_data_no_space(line)))
		return (-1);
	if ((ret = check_redirect_input_error(&begin, line, &data, &name)) < 0)
		return (ret);
	if ((add_back(commands, TYPE_RD_INPUT, name, data) < 0))
		return (-1);
	return (1);
}
