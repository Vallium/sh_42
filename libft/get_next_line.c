/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 14:13:14 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/27 19:21:17 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

typedef struct	s_gnl
{
	t_list		*lst;		// pointeur sur chainon
	char		*pos;		// pointeur sur contenu du chainon
}				t_gnl;

int		len(t_gnl *all)
{
	unsigned int	ret;

	ret = 0;
	while (*all->pos != '\n')
	{
		ret++;
		all->pos++;
		if ((unsigned int)((void*)all->pos - all->lst->content)
			 == all->lst->content_size)											// si fin du maillon
		{
			all->lst = all->lst->next;											// maillon suivant
			if (!all->lst)														// si plus de maillon
				break ;
			all->pos = (char *)(all->lst->content);								// pointeur place au debut du content maillon suivant
		}
	}
	return (ret);
}

void	del(void *ptr, size_t size)
{
	(void)size;
	free(ptr);
}

int		readline(t_gnl *all, char *str)
{
	//char			*localcontent;
	//t_list          *tmp;

	//tmp	= all->lst;
	while (*all->pos != '\n')													// while pas de fin de ligne
	{
		*str++ = *all->pos++;													// copie
		if ((unsigned int)((void*)all->pos - all->lst->content) == all->lst->content_size)											// si fin du maillon
		{
			// free
			//ft_lstdel(lst,del);
			//tmp = tmp->next;
			all->lst = all->lst->next;
			if ((*all->pos != '\n' && !all->lst))
				return (0);
			if (!all->lst)
				return (1);
			all->pos = (char *)(all->lst->content);
		}
	}
	*str = 0;
	all->pos++;
	if ((unsigned int)((void*)all->pos - all->lst->content)
		== all->lst->content_size)											// si fin du maillon
	{
		// free
		all->lst = all->lst->next;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl 		all = {NULL, NULL};
	static int			end = 0;
	int					ret;
	char				buff[BUFF_SIZE];

	if (!line || BUFF_SIZE <= 0 || fd < 0)										// gestion erreur
		return (-1);
	if (!all.lst && !end)
	{
		end = 1;
		while ((ret = read(fd, buff, BUFF_SIZE)))								// while je peut lire
		{
			if (ret == -1)														// si erreur
				return (-1);
			ft_lstsmartpushback(&(all.lst), ft_lstnew((void *)buff, ret));			//save
		}
		all.pos = all.lst->content;
	}
	if (!all.lst && end)														// si plus de ligne
	{
		//ft_lstsimpledel(&lst);
		return (0);
	}
	*line = (char *)malloc(sizeof(char) * (len(&all) + 1));						// malloc une ligne
	return (readline(&all, *line));												// remplie et renvoit une ligne
}
