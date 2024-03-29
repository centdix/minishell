/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:19:12 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 16:54:31 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Run cd command
*/

int		run_cd(t_minishell *minishell)
{
	char	*error;

	if (!ft_strcmp(minishell->commands->data, ""))
	{
		minishell->commands->data = ft_strdup(
get_env_value(minishell->env_variables, "HOME"));
	}
	errno = 0;
	if (chdir(minishell->commands->data) < 0)
	{
		error = strerror(errno);
		write_msg_error(minishell->name, minishell->commands->name, error);
		return (-1);
	}
	free(minishell->path);
	minishell->path = NULL;
	minishell->path = getcwd(minishell->path, 0);
	return (0);
}
