/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:20:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/09 21:59:58 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char *argv[])
{
	t_minishell	minishell;

	(void)argc;
	if (!(minishell.name = ft_strjoin(argv[0], ": ")))
		return (-1);
	while (1)
	{
		if (write(1, minishell.name, ft_strlen(minishell.name)) < 0)
			return (-1);
		if (!(minishell.command = ft_strdup("")))
			return (-1);
		if (!(minishell.command = wait_command(minishell.command)))
			return (-1);
		if (parsing_command(&minishell) < 0)
			return (-1);
		free(minishell.command);
	}
	return (0);
}
