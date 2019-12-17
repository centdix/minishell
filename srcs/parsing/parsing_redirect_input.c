/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirect_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 03:06:32 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 09:04:08 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_redirect_input(char **line, t_lstcommands **commands)
{
	char	*begin;
	char	*name;
	char	*data;

	begin = (*line);
	(*line)++;
	if ((check_too_many_args(line, 1)) < 0)
		return (TOO_MANY_ARGS);
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if (!(data = get_data_no_space(line)))
		return (-1);
	if ((add_back(commands, TYPE_RD_INPUT, name, data) < 0))
		return (-1);
	return (1);
}
