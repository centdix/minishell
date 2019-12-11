/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:59:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 08:01:00 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Sort list of env_variables and return the first element
*/

t_lstenv_v			*sort_envv(t_lstenv_v *lst, size_t size)
{
	t_lstenv_v	*begin;
	t_lstenv_v	*prev;
	t_lstenv_v	*next;

	while (size-- && !(prev = NULL))
	{
		begin = lst;
		while (lst->next)
		{
			next = lst->next;
			if (ft_strcmp(lst->name, next->name) > 0)
			{
				lst->next = next->next;
				next->next = lst;
				lst = next;
				begin = (!prev) ? lst : begin;
				if (prev)
					prev->next = lst;
			}
			prev = lst;
			lst = lst->next;
		}
		lst = begin;
	}
	return (lst);
}

/*
** Get the lstenv_v who's name name
*/

t_lstenv_v			*get_env_variable(t_lstenv_v *lst, char *name)
{
	while (lst)
	{
		if (!ft_strcmp(lst->name, name))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/*
** Get the environment variable who's name name
*/

char				*get_env_value(t_lstenv_v *lst, char *name)
{
	while (lst)
	{
		if (!ft_strcmp(lst->name, name))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

/*
** Create the list of env_variables by adding them one by one to a new lst
** and return it
*/

t_lstenv_v			*init_env(char **envv)
{
	t_lstenv_v	*lst;
	char		*ptr;
	char		*value;
	char		*name;

	lst = NULL;
	while (*envv)
	{
		ptr = ft_strchr(*envv, '=');
		*ptr++ = '\0';
		if (*ptr == '\0' && !(value = NULL))
			ptr = NULL;
		else
		{
			if (!(value = ft_strdup(ptr)))
				return (NULL);
		}
		if (!(name = ft_strdup(*envv)))
			return (NULL);
		if (add_back_env(&lst, name, value) < 0)
			return (NULL);
		envv++;
	}
	return (lst);
}
