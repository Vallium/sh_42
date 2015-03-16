/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot  <aalliot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 14:54:42 by aalliot           #+#    #+#             */
/*   Updated: 2015/01/02 14:55:10 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_swap(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
