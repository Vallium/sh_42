/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 15:30:38 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/19 15:30:40 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_1.h"

int		magic_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
	return (0);
}

int		command_free(char *args[], char *line, char *bin)
{
	char	**tmp;

	tmp = args;
	while (tmp && *tmp)
	{
		free(*tmp);
		*tmp++ = NULL;
	}
	free(args);
	args = NULL;
	free(line);
	line = NULL;
	if (bin)
	{
		free(bin);
		bin = NULL;
	}
	return (0);
}

int		free_home_path(t_cd *cd)
{
	if (cd->path)
		free(cd->path);
	return (0);
}
