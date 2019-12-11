/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:33:01 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 01:31:57 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_env(t_minishell *minishell, char **data)
{
	char		*begin;
	char		*name;
	char		*value;
	t_lstenv_v	*envv;

	begin = (*data);
	if (*(*data) == '=')
		return (-1);
	while (*(*data) && *(*data) != '=' && !ft_isspace(*(*data)))
		(*data)++;
	if (*(*data))
		*(*data)++ = '\0';
	if ((name = ft_strdup(begin)) < 0)
		return (-1);
	if (!*(*data) || ft_isspace(*(*data)))
		value = NULL;
	else
	{
		begin = (*data);
		while (*(*data) && !ft_isspace(*(*data)))
			(*data)++;
		if (*data)
			*(*data)++ = '\0';
		if ((value = ft_strdup(begin)) < 0)
			return (-1);
	}
	if ((envv = get_env_variable(minishell->env_variables, name)))
	{
		envv->value = value;
	}
	else
	{
		if (add_back_env(&minishell->env_variables, name, value) < 0)
			return (-1);
	}
	return (0);
}

/*
** Run export command
*/

int		run_export(t_minishell *minishell)
{
	char		*data;
	t_lstenv_v	*envv;

	envv = minishell->env_variables;
	if (!ft_strcmp(minishell->commands->data, ""))
	{
		while (envv)
		{
			write(1, envv->name, ft_strlen(envv->name));
			write(1, "=", 1);
			if (envv->value)
				write(1, envv->value, ft_strlen(envv->value));
			else
				write(1, "''", 2);
			write(1, "\n", 1);
			envv = envv->next;
		}
	}
	else
	{
		data = minishell->commands->data;
		while (*data)
		{
			if (export_env(minishell, &data) < 0)
				return (-1);
			if (ft_isspace(*data))
				data++;
		}
	}
	return (0);
}
