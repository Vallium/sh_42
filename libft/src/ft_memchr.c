/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
=======
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
>>>>>>> 34dee0d9437f954436363ae126576b3c9e5f32e9
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 18:10:32 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/05 18:16:03 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void						*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*str;

	str = (const unsigned char*)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return ((void*)str);
		str++;
	}
	return (NULL);
}
