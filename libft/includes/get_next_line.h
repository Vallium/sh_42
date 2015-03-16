/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot  <aalliot@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 12:44:13 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/16 20:48:09 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 8

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int				get_next_line(int fd, char **line);

typedef struct	s_gnl
{
	t_list		*lst;
	char		*pos;
}				t_gnl;

#endif
