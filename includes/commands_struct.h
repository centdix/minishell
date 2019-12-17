/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 05:23:57 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 03:13:58 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_STRUCT_H
# define COMMANDS_STRUCT_H

/*
** lstcommands is a command, the type of the command is stored,
** the command and the next command (pipe is considered as a command)
*/

typedef	struct		s_lstcommands
{
	int				type;
	int				pipe[2];
	char			*data;
	void			*prev;
	void			*next;
}					t_lstcommands;

#endif
