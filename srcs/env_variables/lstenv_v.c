/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstenv_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 04:13:20 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 11:38:38 by lmartin          ###   ########.fr       */
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

size_t				get_size_lstenv_v(t_lstenv_v *lst)
{
	size_t		size;
	t_lstenv_v	*ptr;

	size = 0;
	ptr = lst;
	while (ptr && ++size)
		ptr = ptr->next;
	return (size);
}

/*
** Create an array ** with all environment variables
*/

char				**t_lstenv_v_to_array(t_lstenv_v *lst)
{
	t_lstenv_v	*ptr;
	char		*tmp;
	char		**array;
	char		**ptr2;

	if (!(array = malloc(sizeof(char *) * (get_size_lstenv_v(lst) + 1))))
		return (NULL);
	ptr2 = array;
	ptr = lst;
	while (ptr)
	{
		if (!(tmp = ft_strjoin(ptr->name, "=")))
			return (NULL);
		if (ptr->value)
		{
			if (!(*ptr2++ = ft_strjoin(tmp, ptr->value)))
				return (NULL);
		}
		else if (!(*ptr2++ = ft_strdup(tmp)))
			return (NULL);
		free(tmp);
		ptr = ptr->next;
	}
	*ptr2 = NULL;
	return (array);
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
