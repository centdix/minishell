/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:23:15 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 09:05:05 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		header_top(void)
{
	if (write(STDOUT_FILENO, "                                      ", 38) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "                                      \n", 39) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "   \x1b[32mWelcome in :\x1b[0m                 ", 47) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "                                      \n", 39) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "        __  ____       _      __      ", 38) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "   ____                               \n", 39) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "       /  |/  (_)___  (_)____/ /_  ___", 38) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "  / / /        ___ ___                \n", 39) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "      / /|_/ / / __ \\/ / ___/ __ \\/ _ ", 38) < 0)
		return (-1);
	return (0);
}

int		header(void)
{
	if (header_top() < 0)
		return (-1);
	if (write(STDOUT_FILENO, "\\/ / /        | | |_  |               \n", 39) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "     / /  / / / / / / (__  ) / / /  __", 38) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "/ / /         |_  |  _|               \n", 39) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "    /_/  /_/_/_/ /_/_/____/_/ /_/\\___/", 38) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "_/_/            |_|___|.fr            \n", 39) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "                                      ", 38) < 0)
		return (-1);
	if (write(STDOUT_FILENO, "                                      \n", 39) < 0)
		return (-1);
	return (0);
}

int		write_prompt(char *path)
{
	if (write(STDOUT_FILENO, _COLOR1, C_SIZE) < 0)
		return (-1);
	if (write(STDOUT_FILENO, path, ft_strlen(path)) < 0)
		return (-1);
	if (write(STDOUT_FILENO, _END, E_SIZE) < 0)
		return (-1);
	if (write(STDOUT_FILENO, _CYAN, C_SIZE) < 0)
		return (-1);
	if (write(STDOUT_FILENO, _END_PATH, _END_SIZE) < 0)
		return (-1);
	if (write(STDOUT_FILENO, _END, E_SIZE) < 0)
		return (-1);
	return (0);
}
