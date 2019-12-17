/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcommands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:54:06 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 10:01:49 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Free a list of commands
*/

void				free_lstcommands(t_lstcommands **lst)
{
	t_lstcommands	*next;

	while ((*lst))
	{
		next = (*lst)->next;
		if ((*lst)->name)
			free((*lst)->name);
		if ((*lst)->data)
			free((*lst)->data);
		free((*lst));
		(*lst) = next;
	}
}

/*
** Create a element lstcommands with type and data and return it.
** Types are defined in commands.h
*/

t_lstcommands		*new_lstcommands(int type, char *name,
char *data, void *prev)
{
	t_lstcommands *lstcommands;

	if (!(lstcommands = malloc(sizeof(t_lstcommands))))
		return (NULL);
	lstcommands->name = name;
	lstcommands->type = type;
	lstcommands->data = data;
	lstcommands->prev = prev;
	lstcommands->next = NULL;
	return (lstcommands);
}

/*
** Add lstcommands at the end of the chained list or create the list if lst
** is null.
*/

int					add_back(t_lstcommands **lst, int type,
char *name, char *data)
{
	t_lstcommands *begin;

	begin = *lst;
	if (begin)
	{
		while (begin->next)
			begin = begin->next;
		if (!(begin->next = new_lstcommands(type, name, data, begin)))
			return (-1);
	}
	else
	{
		if (!(*lst = new_lstcommands(type, name, data, NULL)))
			return (-1);
		begin = *lst;
	}
	return (0);
}
