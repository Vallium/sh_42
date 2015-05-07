/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsimpledel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
=======
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
>>>>>>> 34dee0d9437f954436363ae126576b3c9e5f32e9
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 16:27:00 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/16 16:28:56 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsimpledel(t_list **alst)
{
	if (*alst)
	{
		ft_lstsimpledel(&(*alst)->next);
		ft_lstsimpledelone(alst);
	}
}
