/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
=======
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
>>>>>>> 34dee0d9437f954436363ae126576b3c9e5f32e9
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 14:57:33 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 14:57:35 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new_list;
	t_list		*start;
	t_list		*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = (*f)(lst);
	new_list = ft_lstnew(tmp->content, tmp->content_size);
	if (!new_list)
		return (NULL);
	start = new_list;
	while (lst->next)
	{
		tmp = f(lst->next);
		ft_lstadd(&new_list->next, ft_lstnew(tmp->content, tmp->content_size));
		if (!new_list)
			return (NULL);
		lst = lst->next;
		new_list = new_list->next;
	}
	return (start);
}
