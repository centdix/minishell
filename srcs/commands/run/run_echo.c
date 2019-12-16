/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:20:16 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/16 02:43:53 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Run echo command
*/

int		run_echo(t_minishell *minishell)
{
	char	*data;
	int		option_n;

	option_n = 0;
	data = minishell->commands->data;
	if (!ft_strncmp(data, "-n", 2) && ft_isspace(data[2]))
	{
		option_n = 1;
		data = &data[2];
		while (data && ft_isspace(*data))
			data++;
	}
	if (write(STDOUT_FILENO, data, ft_strlen(data)) < 0)
		return (ft_setint_and_return(&g_lastreturn, -1));
	if (!option_n && write(STDOUT_FILENO, "\n", 1) < 0)
		return (ft_setint_and_return(&g_lastreturn, -1));
	return (ft_setint_and_return(&g_lastreturn, 0));
}
