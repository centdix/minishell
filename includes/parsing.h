/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:35:53 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 13:09:17 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*
** Parsing utils
*/

int		add_envv_and_move(char **ptr, char **str);
int		count_envv_variable(char **ptr);
void	put_str_to_str(char **dst, char *src);
char	*strdup_to_sep(char **ptr);

/*
** Get data for arguments and parsing names
*/

char	*get_data(char **str);
char	*get_data_one_space(char **str);
char	*get_data_no_space(char **str);

/*
** General parsing
*/

int		parsing_command(t_minishell *minishell);

/*
** Parsing commands
*/

int		parsing_bin(char **line, t_lstcommands **commands);
int		parsing_cd(char **line, t_lstcommands **commands);
int		parsing_echo(char **line, t_lstcommands **commands);
int		parsing_env(char **line, t_lstcommands **commands);
int		parsing_exit(char **line, t_lstcommands **commands);
int		parsing_export(char **line, t_lstcommands **commands);
int		parsing_pwd(char **line, t_lstcommands **commands);
int		parsing_unset(char **line, t_lstcommands **commands);

#endif
