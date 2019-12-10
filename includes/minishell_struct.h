/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 22:55:26 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 05:33:00 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "commands_struct.h"

typedef struct	s_minishell
{
	char			*name;
	char			*command_line;
	char			*path;
	t_lstcommands	*commands;
}				t_minishell;

#endif
