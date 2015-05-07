/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
=======
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
>>>>>>> 34dee0d9437f954436363ae126576b3c9e5f32e9
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:51:09 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 13:38:24 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			*ft_strmap(const char *s, char (*f)(char))
{
	char		*ret;
	char		*str;

	if (s && f)
	{
		str = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
		if (!str)
			return (NULL);
		ret = str;
		while (*s && f && s)
		{
			*str = (*f)(*s);
			str++;
			s++;
		}
		*str = 0;
		return (ret);
	}
	return (NULL);
}
