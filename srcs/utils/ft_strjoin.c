/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:28:20 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/09 20:40:38 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *str;
	char *pt;

	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	pt = str;
	while (*s1)
		*pt++ = *s1++;
	while (*s2)
		*pt++ = *s2++;
	*pt = '\0';
	return (str);
}
