/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:35:53 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 23:22:20 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

char	*get_data(char **str);
char	*get_data_one_space(char **str);
char	*get_data_no_space(char **str);

int		parsing_command(t_minishell *minishell);

int		parsing_cd(char **line, t_lstcommands **commands);
int		parsing_echo(char **line, t_lstcommands **commands);
int		parsing_exit(char **line, t_lstcommands **commands);
int		parsing_pwd(char **line, t_lstcommands **commands);

#endif
