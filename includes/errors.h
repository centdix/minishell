/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:25:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 11:11:36 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define WRONG_ARG -2
# define TOO_MANY_ARGS -3
# define NOT_ENOUGH_ARGS -4
# define CMD_NOT_FOUND -5
# define ERR_PIPE -6
# define ERR_MALLOC -7
# define ERR_WRITE -8

# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_WRONG_ARGS "wrong argument"
# define MSG_NOT_ENOUGH_ARGS "not enough arguments"
# define MSG_TOO_MANY_ARGS "too many arguments"

/*
** Errors about command
*/

int		command_error(char *name, char *cmd_name, int ret);
int		write_msg_error(char *prg_name, char *cmd_name, char *msg);
int		check_too_many_args(char **str, int nb_args_max);

#endif
