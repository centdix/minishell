/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 02:52:19 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/16 06:47:10 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_pipe(char **line, t_lstcommands **commands)
{
	t_lstcommands *ptr;

	(*line)++;
	if ((add_back(commands, TYPE_PIPE, NULL) < 0))
		return (-1);
	ptr = *commands;
	while (ptr->next)
		ptr++;
	if (pipe(ptr->pipe) < 0)
		return (ERR_PIPE);
	return (1);
}
