/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot  <aalliot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/20 11:53:50 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/20 11:53:52 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					len(t_gnl all)
{
	unsigned int	ret;

	ret = 0;
	while (*(all.pos) != '\n')
	{
		ret++;
		all.pos++;
		if ((unsigned int)((void*)all.pos - all.lst->content)
			== all.lst->content_size)
		{
			all.lst = all.lst->next;
			if (!all.lst)
				break ;
			all.pos = (char *)(all.lst->content);
		}
	}
	return (ret);
}

void				del(void *ptr, size_t size)
{
	(void)size;
	free(ptr);
}

void				last(t_gnl *all)
{
	t_list		*tmp;

	if ((unsigned int)((void*)all->pos - all->lst->content)
		== all->lst->content_size)
	{
		if (all->lst)
		{
			tmp = all->lst;
			all->lst = all->lst->next;
			ft_lstdelone(&tmp, del);
			if (all->lst)
				all->pos = all->lst->content;
		}
	}
}

int					readline(t_gnl *all, char *str)
{
	t_list		*tmp;

	while (*all->pos != '\n')
	{
		*str++ = *all->pos++;
		if ((unsigned int)((void*)all->pos - all->lst->content)
				== all->lst->content_size)
		{
			tmp = all->lst;
			all->lst = all->lst->next;
			all->pos = (char *)(all->lst->content);
			ft_lstdelone(&tmp, del);
			if ((*all->pos != '\n' && !all->lst))
				return (0);
			if (!all->lst)
				return (1);
			all->pos = (char *)all->lst->content;
		}
	}
	*str = 0;
	all->pos++;
	last(all);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	all = {NULL, NULL};
	int				ret;
	char			buff[BUFF_SIZE + 1];

	if (!all.lst)
	{
		while ((ret = read(fd, buff, BUFF_SIZE)))
		{
			if (ret == -1)
				return (-1);
			ft_lstsmartpushback(&(all.lst), ft_lstnew((void *)buff, ret));
			buff[ret] = 0;
			if (ft_strchr(buff, '\n'))
				break ;
		}
		if (all.lst)
			all.pos = all.lst->content;
	}
	if (all.lst)
	{
		*line = (char *)malloc(sizeof(char) * (len(all) + 1));
		return (readline(&all, *line));
	}
	return (0);
}
