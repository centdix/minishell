/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:20:27 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 12:12:24 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Run pwd command
*/

int		run_pwd(t_minishell *minishell)
{
	if (write(STDOUT_FILENO, minishell->path, ft_strlen(minishell->path)) < 0)
		return (ft_setint_and_return(&g_lastreturn, -1));
	if (write(STDOUT_FILENO, "\n", 1) < 0)
		return (ft_setint_and_return(&g_lastreturn, -1));
	return (ft_setint_and_return(&g_lastreturn, 0));
}
