/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcommands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:54:06 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 06:33:36 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Create a element lstcommands with type and data and return it.
** Types are defined in commands.h
*/

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

/*
** Add lstcommands at the end of the chained list or create the list if lst
** is null.
*/

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
