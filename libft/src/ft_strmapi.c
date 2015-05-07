/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
=======
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
>>>>>>> 34dee0d9437f954436363ae126576b3c9e5f32e9
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 17:22:30 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 13:49:23 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char				*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*ret;
	size_t			l;
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		l = ft_strlen(s);
		ret = (char*)malloc(sizeof(char) * (l + 1));
		if (!ret)
			return (NULL);
		while (i < l)
		{
			ret[i] = (*f)(i, *s++);
			i++;
		}
		ret[i] = 0;
		return (ret);
	}
	return (NULL);
}
