/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:33:01 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 12:12:16 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Set value for export_env
*/

int		export_set_value(t_minishell *minishell, char **begin, char **data)
{
	t_lstenv_v	*envv;
	char		*name;
	char		*value;

	value = NULL;
	if (*(*data))
		*(*data)++ = '\0';
	if ((name = ft_strdup(*begin)) < 0)
		return (-1);
	if (*(*data) && !ft_isspace(*(*data) && (*begin = (*data))))
	{
		while (*(*data) && !ft_isspace(*(*data)))
			(*data)++;
		if (**data)
			*(*data)++ = '\0';
		if ((value = ft_strdup(*begin)) < 0)
			return (-1);
	}
	if ((envv = get_env_variable(minishell->env_variables, name)))
		envv->value = value;
	else if (add_back_env(&minishell->env_variables, name, value) < 0)
		return (-1);
	return (0);
}

/*
** Parse data and add or modify existing env_variables
*/

int		export_export_env(t_minishell *minishell, char **data)
{
	char		*begin;
	t_lstenv_v	*envv;
	char		*name;

	if (((begin = (*data)) || !begin) && *(*data) == '=')
		return (-1);
	while (*(*data) && *(*data) != '=' && !ft_isspace(*(*data)))
	{
		if (!ft_isalpha(**data) && !ft_isdigit(**data) && **data != '_')
			return (-2);
		(*data)++;
	}
	if (*(*data) != '=')
	{
		if (*(*data))
			*(*data)++ = '\0';
		if (((name = ft_strdup(begin)) < 0) ||
(!(envv = get_env_variable(minishell->env_variables, name)) &&
add_back_env(&minishell->env_variables, name, NULL) < 0))
			return (-1);
	}
	else if (export_set_value(minishell, &begin, &(*data)) < 0)
		return (-1);
	return (0);
}

/*
** Write env_variables
*/

int		export_write_envv(t_lstenv_v *envv)
{
	if (write(1, envv->name, ft_strlen(envv->name)) < 0)
		return (-1);
	if (write(1, "=", 1) < 0)
		return (-1);
	if (envv->value && write(1, envv->value, ft_strlen(envv->value)) < 0)
		return (-1);
	else if (!envv->value && write(1, "''", 2) < 0)
		return (-1);
	if (write(1, "\n", 1) < 0)
		return (-1);
	return (0);
}

/*
** Sort lstenv_v and write
*/

int		sort_and_write_envv(t_lstenv_v *envv)
{
	t_lstenv_v	*sorted;
	size_t		size;

	size = 0;
	sorted = NULL;
	while (envv && ++size)
	{
		if (add_back_env(&sorted, envv->name, envv->value) < 0)
			return (-1);
		envv = envv->next;
	}
	sorted = sort_envv(sorted, size);
	while (sorted && (envv = sorted))
	{
		if (export_write_envv(sorted) < 0)
			return (-1);
		sorted = sorted->next;
		free(envv);
	}
	return (0);
}

/*
** Run export command
*/

int		run_export(t_minishell *minishell)
{
	int			ret;
	char		*data;
	t_lstenv_v	*envv;

	envv = minishell->env_variables;
	if (!ft_strcmp(minishell->commands->data, ""))
	{
		if (sort_and_write_envv(envv) < 0)
			return (ft_setint_and_return(&g_lastreturn, -1));
	}
	else
	{
		data = minishell->commands->data;
		while (*data)
		{
			ret = export_export_env(minishell, &data);
			if (ret == -1)
				return (ft_setint_and_return(&g_lastreturn, -1));
			if (ret == -2)
				return (ft_setint_and_return(&g_lastreturn, 1)); // ERREUR A GERER
			if (ft_isspace(*data))
				data++;
		}
	}
	return (ft_setint_and_return(&g_lastreturn, 0));
}
