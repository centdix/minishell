/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 22:55:26 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 12:10:58 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include "commands_struct.h"
# include "env_variables.h"

typedef struct	s_minishell
{
	pid_t			pid;
	char			*name;
	char			*command_line;
	char			*path;
	t_lstcommands	*commands;
	t_lstenv_v		*env_variables;
}				t_minishell;

#endif
