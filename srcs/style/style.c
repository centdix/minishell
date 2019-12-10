/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:23:15 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 09:25:04 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		header_top()
{
	if (write(1, "                                      ", 38) < 0)
		return (-1);
	if (write(1, "                                      \n", 39) < 0)
		return (-1);
	if (write(1, "   \x1b[32mWelcome in :\x1b[0m                 ", 47) < 0)
		return (-1);
	if (write(1, "                                      \n", 39) < 0)
		return(-1);
	if (write(1, "        __  ____       _      __      ", 38) < 0)
		return(-1);
	if (write(1, "   ____                               \n", 39) < 0)
		return(-1);
	if (write(1, "       /  |/  (_)___  (_)____/ /_  ___", 38) < 0)
		return(-1);
	if (write(1, "  / / /        ___ ___                \n", 39) < 0)
		return(-1);
	if (write(1, "      / /|_/ / / __ \\/ / ___/ __ \\/ _ ", 38) < 0)
		return(-1);
	return (0);
}

int		header()
{
	if (header_top() < 0)
		return(-1);
	if (write(1, "\\/ / /        | | |_  |               \n", 39) < 0)
		return(-1);
	if (write(1, "     / /  / / / / / / (__  ) / / /  __", 38) < 0)
		return(-1);
	if (write(1, "/ / /         |_  |  _|               \n", 39) < 0)
		return(-1);
	if (write(1, "    /_/  /_/_/_/ /_/_/____/_/ /_/\\___/", 38) < 0)
		return(-1);
	if (write(1, "_/_/            |_|___|.fr            \n", 39) < 0)
		return(-1);
	if (write(1, "                                      ", 38) < 0)
		return(-1);
	if (write(1, "                                      \n", 39) < 0)
		return(-1);
	return (0);
}

int		write_prompt(char *path)
{
	if (write(1, _COLOR1, C_SIZE) < 0)
		return (-1);
	if (write(1, path, ft_strlen(path)) < 0)
		return (-1);
	if (write(1, _END, E_SIZE) < 0)
		return (-1);
	if (write(1, _CYAN, C_SIZE) < 0)
		return (-1);
	if (write(1, _END_PATH, _END_SIZE) < 0)
		return (-1);
	if (write(1, _END, E_SIZE) < 0)
		return (-1);
	return (0);
}
