/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 02:25:01 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 04:42:04 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Set value for export_env
*/

int		env_set_value(char **value, char *begin, char **data)
{
	if (!*(*data) || ft_isspace(*(*data)))
		*value = NULL;
	else if ((begin = (*data)))
	{
		while (*(*data) && !ft_isspace(*(*data)))
			(*data)++;
		if (**data)
			*(*data)++ = '\0';
		if ((*value = ft_strdup(begin)) < 0)
			return (-1);
	}
	return (0);
}

/*
** Parse data and add or modify existing env_variables
*/

int		env_export_env(t_lstenv_v *env_variables, char **data)
{
	char		equal;
	char		*begin;
	char		*name;
	char		*value;
	t_lstenv_v	*envv;

	if ((!(begin = (*data)) || begin) && *(*data) == '=')
		return (-2);
	while ((equal = **data) && *(*data) != '=' && !ft_isspace(*(*data)))
		(*data)++;
	if (*(*data))
		*(*data)++ = '\0';
	if ((name = ft_strdup(begin)) < 0)
		return (-1);
	if (!(envv = get_env_variable(env_variables, name)) && equal != '=')
		return (ft_free_return(name));
	if (equal != '=')
		return (1);
	if (env_set_value(&value, begin, &(*data)) < 0)
		return (-1);
	if ((envv = get_env_variable(env_variables, name)))
		envv->value = value;
	else if (add_back_env(&env_variables, name, value) < 0)
		return (-1);
	return (0);
}

/*
** Write env_variables
*/

int		env_write_envv(t_lstenv_v *envv)
{
	if (write(STDOUT_FILENO, envv->name, ft_strlen(envv->name)) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "=", 1) < 0)
		return (-1);
	if (envv->value && write(STDOUT_FILENO, envv->value,
ft_strlen(envv->value)) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		return (-1);
	return (0);
}

/*
** Add new envv with data in a envv buffer (not in the minishell's one)
*/

int		add_and_write_envv(t_minishell *minishell)
{
	int			ret;
	t_lstenv_v	*envv;
	t_lstenv_v	*new;
	char		*data;

	new = NULL;
	envv = minishell->env_variables;
	while (envv && (data = minishell->commands->data))
		if (add_back_env(&new, envv->name, envv->value) < 0 ||
(!(envv = envv->next) && envv))
			return (-1);
	while (*data)
	{
		if ((ret = env_export_env(new, &data)) != 0)
			return (ret); // A FAIRE GESTION ERREURS
		data = (ft_isspace(*data)) ? data + 1 : data;
	}
	while (new && (envv = new))
	{
		if (env_write_envv(new) < 0 || (!(new = new->next) && new))
			return (-1);
		ft_multifree(envv->value, envv->name, envv, NULL);
	}
	return (0);
}

/*
** Run export command
*/

int		run_env(t_minishell *minishell)
{
	int			ret;
	t_lstenv_v	*envv;

	envv = minishell->env_variables;
	if (!ft_strcmp(minishell->commands->data, ""))
	{
		while (envv)
		{
			if (env_write_envv(envv) < 0)
				return (ft_setint_and_return(&g_lastreturn, -1));
			envv = envv->next;
		}
	}
	else
	{
		ret = add_and_write_envv(minishell);
		if (ret == -1)
			return (ft_setint_and_return(&g_lastreturn, ret));
		else if (ret == -2)
			return (ft_setint_and_return(&g_lastreturn, 0)); // ERREUR A FAIRE NO SUCH FILE OR DIRECTORY
	}
	return (ft_setint_and_return(&g_lastreturn, 0));
}
