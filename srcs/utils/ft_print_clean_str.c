/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_clean_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:37:33 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 18:44:07 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print a clean string without backslash, environment variable when needed etc.
*/

int		ft_print_clean_str(char *data)
{
	int		d;
	char	*tmp;
	char	*value;

	while (*data)
	{
		d = 0;
		while (*data == '\\' && ++d)
			data++;
		if (*data == '$' && !(d % 2))
		{
			data++;
			if (*data)
			{
				if (!(tmp = strdup_to_sep(&data)))
					return (-1);
				if ((value = get_env_value(g_envv, tmp)))
					if (write(1, value, ft_strlen(value)))
						return (-1);
				data += ft_strlen(tmp);
				free(tmp);
			}
		}
		else if (write(1, data++, 1) < 0)
			return (-1);
	}
	return (0);
}
