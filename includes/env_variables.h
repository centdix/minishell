/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 09:52:50 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 10:21:23 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VARIABLES_H
# define ENV_VARIABLES_H

typedef	struct		s_lstenv_v
{
	char			*name;
	char			*value;
	void			*next;
}					t_lstenv_v;

t_lstenv_v			*new_lstenv_v(char *name, char *value);
int					add_back_env(t_lstenv_v **lst, char *name, char *value);
char				*get_env_value(t_lstenv_v *lst, char *name);
t_lstenv_v			*init_env(char **envv);

#endif
