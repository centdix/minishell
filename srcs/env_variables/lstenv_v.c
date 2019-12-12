/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstenv_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 04:13:20 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 03:36:33 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Create a new lstenv_v to store a environment variable
*/

t_lstenv_v			*new_lstenv_v(char *name, char *value)
{
	t_lstenv_v *lstenv_v;

	if (!(lstenv_v = malloc(sizeof(t_lstenv_v))))
		return (NULL);
	lstenv_v->name = name;
	lstenv_v->value = value;
	lstenv_v->next = NULL;
	return (lstenv_v);
}

/*
** Create a new env_variables and add it at the end of the lst (or create a new
** list if lst is NULL)
*/

int					add_back_env(t_lstenv_v **lst, char *name, char *value)
{
	t_lstenv_v *begin;

	begin = *lst;
	if (begin)
	{
		while (begin->next)
			begin = begin->next;
		if (!(begin->next = new_lstenv_v(name, value)))
			return (-1);
	}
	else
	{
		if (!(*lst = new_lstenv_v(name, value)))
			return (-1);
		begin = *lst;
	}
	return (0);
}

/*
** Return size of lstenv_v
*/

size_t	get_size_lstenv_v(t_lstenv_v	*lst)
{
	size_t		size;
	t_lstenv_v	*ptr;

	size = 0;
	ptr = lst;
	while (ptr && ++size)
		ptr = ptr->next;
	return (size);
}
