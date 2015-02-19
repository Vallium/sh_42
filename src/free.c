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

int		free_home_path(t_list *env, t_cd *cd)
{
	cd->old = get_elem(env, "OLDPWD");
	cd->pwd = get_elem(env, "PWD");

	t_list_elem elem;



	if (!cd->pwd)
	{
		elem.key = ft_strdup("PATH");
		elem.data = getwd(0);
		ft_lstsmartpushback(&env, ft_lstnew(&senv.new, sizeof(t_list_elem)));
	}

	if (cd->old)
	{
		free(cd->old->data);
		cd->old->data = cd->pwd->data;
	if (chdir(cd->path))
		print_error(3, cd->path);
	cd->pwd->data = getwd(0);
	if (cd->path)
		free(cd->path);
	return (0);
}

void	free_path(t_path *path)
{
	path->tmp = path->paths;
	while (*path->tmp)
	{
		free(*(path->tmp));
		*path->tmp = NULL;
		path->tmp++;
	}
	free(path->paths);
}
