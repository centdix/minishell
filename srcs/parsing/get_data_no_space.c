/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_no_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:50:07 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 18:07:41 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get the size to allocate on get_data_no_space
*/

int		get_data_no_space_size(char **str)
{
	char	*ptr;
	int		ret;
	int		size;

	while (ft_isspace(**str))
		(*str)++;
	ptr = *str;
	size = 0;
	while (!ft_isspace(*ptr) && !ft_isseparator(*ptr) && *ptr)
	{
		if (*ptr == '\\')
			(*ptr)++;
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
** Get data (argument), until white space or separator or end
*/

char	*get_data_no_space(char **str)
{
	char	*data;
	char	*ptr;
	int		size;

	if ((size = get_data_no_space_size(str)) < 0)
		return (NULL);
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ptr = data;
	while (!ft_isspace(**str) && !ft_isseparator(**str) && **str)
	{
		if (*(*str) == '\\')
			(*str)++;
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
