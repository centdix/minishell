/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 02:52:19 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 03:13:11 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_pipe(char **line, t_lstcommands **commands)
{
	(*line)++;
	if ((add_back(commands, TYPE_PIPE, NULL) < 0))
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	return (1);
}
