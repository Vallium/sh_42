/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
=======
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
>>>>>>> 34dee0d9437f954436363ae126576b3c9e5f32e9
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 17:29:21 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/06 10:35:41 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void						*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*strdst;
	const unsigned char		*strsrc;

	strdst = (unsigned char*)dst;
	strsrc = (const unsigned char*)src;
	if (!len)
		return (dst);
	if (strsrc < strdst)
	{
		strdst += len;
		strsrc += len;
		while (len--)
			*--strdst = *--strsrc;
	}
	else
		while (len--)
			*strdst++ = *strsrc++;
	return (dst);
}
