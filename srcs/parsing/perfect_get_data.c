/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perfect_get_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:03:25 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 19:59:09 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		perfect_get_data_size(char *str)
{
	int		ret;
	int		size;
	char	quote;
	char	escaped;

	quote = 0;
	escaped = 0;
	while (*str && !ft_isseparator(*str))
	{
		if (*str == '\\')
		{
			str += (*(str + 1)) ? 2 : 1;
			size++;
		}
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'' && !ft_isseparator(*str))
			{
				size++;
				str++;
			}
		}
		else if (str == '\"')
		{
			str++
			while (*str && *str != '\"' && !ft_isseparator(*str))
			{
				if (*(*str) == '$' && (!ft_isalpha((*((*str) + 1))) ||
!ft_isdigit(*((*str) + 1)) || (*((*str) + 1)) == '_'))
				{
					++(*str);
					if ((ret = count_envv_variable(&str)) < 0)
						return (-1);
					size += ret;
				}
				else
					str++;
			}
		}
		if (*str)
			str++;
	}
}

/*
** Replace backslash, env_variables, and quote when it should
*/

char	*perfect_get_data(char **str)
{
	while (ft_isspace(**str))
		(*str)++;

}
