/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcommands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:54:06 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 06:04:11 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstcommands		*new_lstcommands(int type, char *data)
{
	t_lstcommands *lstcommands;

	if (!(lstcommands = malloc(sizeof(t_lstcommands))))
		return (NULL);
	lstcommands->type = type;
	lstcommands->data = data;
	lstcommands->next = NULL;
	return (lstcommands);
}

int					add_back(t_lstcommands **lst, int type, char *data)
{
	t_lstcommands *begin;

	begin = *lst;
	if (begin)
	{
		while (begin->next)
			begin = begin->next;
		if (!(begin->next = new_lstcommands(type, data)))
			return (-1);
	}
	else
	{
		if (!(*lst = new_lstcommands(type, data)))
			return (-1);
		begin = *lst;
	}
	return (0);
}
