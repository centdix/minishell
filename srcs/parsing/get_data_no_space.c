/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_no_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:50:07 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 11:48:07 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Get the size of char or ' ' " "
*/

int		get_data_no_space_char_size(char **ptr, int *size)
{
	if (*(*ptr) == '\\' && *((*ptr) + 1) && ((*ptr) += 2))
		(*size)++;
	else if (*(*ptr) == '\'' && (*ptr)++)
	{
		while (*(*ptr) && *(*ptr) != '\'' &&
!ft_isseparator(*(*ptr)) && ++((*size)))
			(*ptr)++;
		(*ptr) += (*(*ptr) == '\'') ? 1 : 0;
	}
	else if (*(*ptr) == '\"' && (*ptr)++)
	{
		while (*(*ptr) && *(*ptr) != '\"' && !ft_isseparator(*(*ptr)))
		{
			if (*(*ptr) == '\\' && ++(*size))
				(*ptr) += (*((*ptr) + 1)) ? 2 : 1;
			else if (check_envv_and_size(ptr, size) < 0)
				return (-1);
		}
		(*ptr) += (*(*ptr) == '\"') ? 1 : 0;
	}
	else if (check_envv_and_size(ptr, size) < 0)
		return (-1);
	return (0);
}

/*
** Get the size to allocate on get_data_no_space
*/

int		get_data_no_space_size(char **str)
{
	char	*ptr;
	int		size;

	while (ft_isspace(**str))
		(*str)++;
	ptr = *str;
	size = 0;
	while (!ft_isspace(*ptr) && !ft_isseparator(*ptr) && *ptr)
	{
		if (get_data_no_space_char_size(&ptr, &size) < 0)
			return (-1);
	}
	return (size);
}

/*
** Get data char
*/

int		get_data_no_space_char(char **str, char **ptr)
{
	if (**str == '\\' && *((*str) + 1) && (*str)++)
		*(*ptr)++ = *(*str)++;
	else if (**str == '\'' && (*str)++)
	{
		while (**str && **str != '\'' && !ft_isseparator(**str))
			*(*ptr)++ = *(*str)++;
		(*str) += (**str == '\'') ? 1 : 0;
	}
	else if (**str == '\"' && (*str)++)
	{
		while (**str && **str != '\"' && !ft_isseparator(**str))
		{
			if (**str == '\\' && (*str)++)
				*(*ptr)++ = *(*str)++;
			else if (check_envv_and_move(str, ptr) < 0)
				return (-1);
		}
		(*str) += (**str == '\"') ? 1 : 0;
	}
	else if (check_envv_and_move(str, ptr) < 0)
		return (-1);
	return (0);
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
		if (get_data_no_space_char(str, &ptr) < 0)
			return (NULL);
	}
	*ptr = '\0';
	return (data);
}
