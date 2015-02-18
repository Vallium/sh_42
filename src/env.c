/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 12:56:24 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/17 12:56:25 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_1.h"

t_list	*get_env(char *envp[])
{
	t_list_elem	elem;
	t_list		*env;
	char		**tmp;
	char		*chr;

	env = NULL;
	tmp = envp;
	while (tmp && *tmp)
	{
		chr = ft_strchr(*tmp, '=');
		elem.key = ft_strsub(*tmp, 0, chr - *tmp);
		elem.data = ft_strdup(chr + 1);
		ft_lstsmartpushback(&env, ft_lstnew(&elem, sizeof(t_list_elem)));
		tmp++;
	}
	return (env);
}

char	*get_data(t_list *env, char *key)
{
	t_list		*tmp;
	t_list_elem	*elem;

	tmp = env;
	while (tmp)
	{
		elem = tmp->content;
		if (!ft_strcmp(elem->key, key))
			return (elem->data);
		tmp = tmp->next;
	}
	return (NULL);
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

char	*get_path(t_list *env, char *bin)
{
	t_path		path;

	path.path = get_data(env, "PATH");
	if (!path.path || !stat(bin, &path.stat_buff))
		return (ft_strdup(bin));
	path.paths = ft_strsplit(path.path, ':');
	path.tmp = path.paths;
	path.ret = NULL;
	while (*path.tmp)
	{
		ft_kebab(path.buff, *(path.tmp), "/", bin, NULL);
		if (!stat(path.buff, &path.stat_buff))
		{
			if (!(path.stat_buff.st_mode & 1))
				path.ret = (char*)1;
			else
				path.ret = ft_strdup(path.buff);
			break ;
		}
		(path.tmp)++;
	}
	free_path(&path);
	return (path.ret);
}

char	**env_to_str(t_list *env)
{
	char		**strenv;
	t_list		*tmp;
	t_list_elem	*elem;
	int			i;
	int			size;

	tmp = env;
	size = ft_lstlen(env);
	strenv = (char**)ft_malloc(sizeof(char*) * (size + 1));
	i = 0;
	while (tmp)
	{
		elem = tmp->content;
		strenv[i] = ft_burger(elem->key, '=', elem->data);
		i++;
		tmp = tmp->next;
	}
	strenv[i] = NULL;
	return (strenv);
}
