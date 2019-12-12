/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:03:25 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 17:08:43 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get the size to allocate on get_data
*/

int		get_data_size(char **str)
{
	int			ret;
	char		*ptr;
	int			size;

	while (ft_isspace(**str))
		(*str)++;
	ptr = *str;
	size = 0;
	while (!ft_isseparator(*ptr) && *ptr)
	{
		if (*ptr == '\\' && ++size)
			ptr++;
		if ((*(ptr - 1)) != '\\' &&
*ptr == '$' && (!ft_isalpha((*(ptr + 1))) ||
!ft_isdigit(*(ptr + 1)) || (*(ptr + 1)) == '_'))
		{
			++ptr;
			if ((ret = count_envv_variable(&ptr)) < 0)
				return (-1);
			size += ret;
		}
		else if (++size)
			ptr++;
	}
	return (size);
}

/*
** Get data (argument), until separator or end
*/

char	*get_data(char **str)
{
	char		*data;
	char		*ptr;
	int			size;

	if ((size = get_data_size(str)) < 0)
		return (NULL);
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ptr = data;
	while (!ft_isseparator(**str) && **str)
	{
		if (**str == '\\')
			*ptr++ = *(*str)++;
		if ((*((*str) - 1)) != '\\' && **str == '$' &&
(!ft_isalpha((*(*str + 1))) ||
!ft_isdigit(*(*str + 1)) || (*(*str + 1)) == '_'))
		{
			++(*str);
			if (add_envv_and_move(&ptr, str) < 0)
				return (NULL);
		}
		else
			*ptr++ = *(*str)++;
	}
	*ptr = '\0';
	return (data);
}
