/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:10:43 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/09 22:50:55 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char *cpy;
	char *pt;

	if (!(cpy = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	pt = cpy;
	while (*s1)
	{
		if ((int)*s1 != ESC_CHAR)
			*pt++ = *s1;
		else
		{
			*pt++ = '^';
			*pt++ = '[';
		}
		s1++;
	}
	*pt = '\0';
	return (cpy);
}
