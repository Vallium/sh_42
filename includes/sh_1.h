/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 12:45:08 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/13 12:45:10 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_1_H
# define SH_1_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <sys/stat.h>

# ifdef __APPLE__
#  include <sys/types.h>
# elif __linux
#  include <sys/types.h>
#  include <sys/wait.h>
# endif

typedef struct	s_list_elem
{
	char		*key;
	char		*data;
}				t_list_elem;

#endif
