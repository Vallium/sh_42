/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
=======
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
>>>>>>> 34dee0d9437f954436363ae126576b3c9e5f32e9
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:15:02 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/05 13:31:54 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	l;
	size_t	i;

	l = ft_strlen(src);
	i = 0;
	while (n > 0)
	{
		if (i > l)
			dst[i] = 0;
		else
			dst[i] = src[i];
		i++;
		n--;
	}
	return (dst);
}
