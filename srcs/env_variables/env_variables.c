/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:59:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 02:18:55 by lmartin          ###   ########.fr       */
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

	lst = NULL;
	while (*envv)
	{
		ptr = ft_strchr(*envv, '=');
		*ptr++ = '\0';
		if (*ptr == '\0')
			ptr = NULL;
		if (add_back_env(&lst, *envv, ptr) < 0)
			return (NULL);
		envv++;
	}
	return (lst);
}
