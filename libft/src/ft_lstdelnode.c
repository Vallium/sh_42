/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot  <aalliot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:34:08 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/15 19:34:10 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	rm(void *content, size_t size)
{
	(void)size;
	free(content);
}

void	ft_lstdelnode(t_list **lst)
{
	if ((*lst)->next != NULL)
	{
		(*lst)->content = NULL;
		(*lst)->content = (*lst)->next->content;
		(*lst)->content_size = (*lst)->next->content_size;
		(*lst)->next = (*lst)->next->next;
	}
	else
		(*lst)->content = NULL;
}
