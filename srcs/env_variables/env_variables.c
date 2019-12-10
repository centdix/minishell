/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:59:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 10:23:55 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char		*get_env_value(t_lstenv_v *lst, char *name)
{
	while (lst)
	{
		if (!ft_strcmp(lst->name, name))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

t_lstenv_v	*init_env(char **envv)
{
	t_lstenv_v	*lst;
	char *ptr;

	lst = NULL;
	while (*envv)
	{
		ptr = ft_strchr(*envv, '=');
		*ptr++ = '\0';
		if (add_back_env(&lst, *envv, ptr) < 0)
			return (NULL);
		envv++;
	}
	return (lst);
}
