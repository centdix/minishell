/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:48:49 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 13:43:41 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check for environment variable ($thing) and get size
*/

int		check_envv_and_size(char **str, int *size)
{
	int		ret;

	if (*(*str) == '$' && (!ft_isalpha((*((*str) + 1))) ||
!ft_isdigit(*((*str) + 1)) || (*((*str) + 1)) == '_' ||
(*((*str) + 1)) == '?') && ++(*str))
	{
		if ((ret = count_envv_variable(&(*str))) < 0)
			return (-1);
		(*size) += ret;
	}
	else if (++(*size))
		(*str)++;
	return (0);
}

/*
** Check for environment variable ($thing) and call add_envv_and_move
*/

int		check_envv_and_move(char **str, char **data)
{
	if (*(*str) == '$' && (!ft_isalpha((*((*str) + 1))) ||
!ft_isdigit(*((*str) + 1)) || (*((*str) + 1)) == '_' ||
(*((*str) + 1)) == '?') && (*str)++)
	{
		if (add_envv_and_move(data, str) < 0)
			return (-1);
	}
	else
		*(*data)++ = *(*str)++;
	return (0);
}

/*
** Add an environment value to a char and move the two pointer (one for the
** size of the value and the other the size of his key)
*/

int		add_envv_and_move(char **ptr, char **str)
{
	char	*tmp;
	char	*value;

	if (!(tmp = strdup_to_sep(str)))
		return (-1);
	value = get_env_value(g_envv, tmp);
	(*str) += ft_strlen(tmp);
	free(tmp);
	tmp = value;
	if (value)
	{
		while (*tmp)
			*(*ptr)++ = *tmp++;
		if (!ft_strcmp(value, "?"))
			free(value);
	}
	return (0);
}

/*
** Count the size of a envv variable in a string pointed by ptr and move pointer
*/

int		count_envv_variable(char **ptr)
{
	char	*tmp;
	char	*value;
	int		ret;

	if (!(tmp = strdup_to_sep(ptr)))
		return (-1);
	value = get_env_value(g_envv, tmp);
	free(tmp);
	if (value)
	{
		ret = ft_strlen(value);
		if (!ft_strcmp(value, "?"))
			free(value);
	}
	else
		ret = 0;
	return (ret);
}

/*
** Allocate a new string which stop to space, separator or end of the ptr string
*/

char	*strdup_to_sep(char **begin)
{
	char	saved_char;
	char	*ptr;
	char	*str;

	ptr = *begin;
	while (*ptr && (ft_isalpha(*ptr) || ft_isdigit(*ptr) || (*ptr == '_') ||
*ptr == '?'))
		ptr++;
	saved_char = *ptr;
	*ptr = '\0';
	if (!(str = ft_strdup(*begin)))
		return (NULL);
	*ptr = saved_char;
	return (str);
}
