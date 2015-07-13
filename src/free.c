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

int		command_free(char *args[], char *bin)
{
	char			**tmp;
	struct stat		stat_buff;

	lstat(bin, &stat_buff);
	tmp = args;
	// if (!stat(line, &stat_buff) && S_ISDIR(stat_buff.st_mode))
	// 	return (0);
	while (tmp && *tmp)
	{
		free(*tmp);
		*tmp++ = NULL;
	}
	free(args);
	args = NULL;
	// free(line);
	// line = NULL;
	if (bin && (stat_buff.st_mode & 1))
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
	if (!cd->pwd)
	{
		cd->elem.key = ft_strdup("PWD");
		cd->elem.data = GET_CWD;
		ft_lstsmartpushback(&env, ft_lstnew(&cd->elem, sizeof(t_list_elem)));
		cd->pwd = get_elem(env, "PWD");
	}
	if (cd->old)
		free(cd->old->data),
		cd->old->data = cd->pwd->data;
	else
	{
		cd->elem.key = ft_strdup("OLDPWD");
		cd->elem.data = GET_CWD;
		ft_lstsmartpushback(&env, ft_lstnew(&cd->elem, sizeof(t_list_elem)));
	}
	if (chdir(cd->path))
		print_error(3, cd->path);
	cd->pwd->data = GET_CWD;
	if (cd->path)
		free(cd->path);
		printf("pwd = %s\n", getwd(0));
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
