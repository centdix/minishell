/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:36:02 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 09:23:46 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STYLE_H
# define STYLE_H

# define C_SIZE		5
# define E_SIZE		4

# define _END		"\x1b[0m"
# define _BOLD		"\x1b[1m"
# define _UNDER		"\x1b[4m"
# define _REV		"\x1b[7m"

# define _GREY		"\x1b[30m"
# define _RED		"\x1b[31m"
# define _GREEN		"\x1b[32m"
# define _YELLOW	"\x1b[33m"
# define _BLUE		"\x1b[34m"
# define _PURPLE	"\x1b[35m"
# define _CYAN		"\x1b[36m"
# define _WHITE		"\x1b[37m"

# define _IGREY		"\x1b[40m"
# define _IRED		"\x1b[41m"
# define _IGREEN	"\x1b[42m"
# define _IYELLOW	"\x1b[43m"
# define _IBLUE		"\x1b[44m"
# define _IPURPLE	"\x1b[45m"
# define _ICYAN		"\x1b[46m"
# define _IWHITE	"\x1b[47m"

# define PERSO_S	6

# define _COLOR1	"\x1b[94m"

# define _END_PATH	" » "
# define _END_SIZE	4

int		header();
int		write_prompt(char *path);

#endif
