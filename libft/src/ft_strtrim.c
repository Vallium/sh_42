/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot  <aalliot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 11:57:43 by aalliot           #+#    #+#             */
/*   Updated: 2014/11/10 16:36:28 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned int		ft_sp(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char					*ft_strtrim(char *s)
{
	char				*dst;
	char				*tmp;
	t_cpl				c;

	tmp = s;
	if (!s)
		return (NULL);
	c.i = 0;
	while (ft_sp(*s++))
		c.i++;
	s -= c.i + 1;
	c.e = ft_strlen(s) - 1;
	if (!*s || c.e == c.i - 1)
	{
		free(tmp);
		return (dst = ft_strnew(1));
	}
	if (c.i != (c.e + 1))
		while (ft_sp(s[c.e]))
			c.e--;
	dst = ft_strsub(s, c.i, (c.e - c.i + 1));
	free(tmp);
	return (dst);
}
