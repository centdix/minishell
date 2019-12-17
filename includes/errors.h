/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:25:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 06:02:08 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define WRONG_ARG -2
# define TOO_MANY_ARGS -3
# define NOT_ENOUGH_ARGS -4
# define ERR_PIPE -5

/*
** Errors about command
*/

int		write_msg_error(char *prg_name, char *cmd_name, char *msg);
int		command_not_found(char *name, char *command);
int		check_too_many_args(char **str, int nb_args_max);

#endif
