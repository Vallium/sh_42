/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 12:56:07 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/17 12:56:09 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_1.h"

int		c_env(t_list *env, char *args[])
{
	t_list		*tmp;
	t_list_elem	*elem;

	if ((!ft_strcmp(args[0], "env") || !ft_strcmp(args[0], "setenv")) && !args[1])
	{
		if (args[1] != NULL)
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": no such file or directory", 2);
			return (1);
		}
		tmp = env;
		while (tmp)
		{
			elem = tmp->content;
			ft_putstr(elem->key);
			ft_putchar('=');
			ft_putendl(elem->data);
			tmp = tmp->next;
		}
		return (1);
	}
	return (0);
}

int		c_setenv(t_list **env, char *args[])
{
	t_setenv	senv;

	senv.tmp = *env;
	if (ft_strcmp(args[0], "setenv") || !args[1] || !args[1][0])
		return (0);
	if (args[2] && args[3])
	{
		ft_putendl_fd("setenv: too many arguments.", 2);
		return (1);
	}
	while (senv.tmp != NULL)
	{
		senv.elem = senv.tmp->content;
		if (!ft_strcmp(senv.elem->key, args[1]))
		{
			free(senv.elem->data);
			senv.elem->data = (args[2] ? ft_strdup(args[2]) : ft_strnew(1));
			return (1);
		}
		senv.tmp = senv.tmp->next;
	}
	senv.new.key = ft_strdup(args[1]);
	senv.new.data = args[2] ? ft_strdup(args[2]) : ft_strnew(1);
	ft_lstsmartpushback(env, ft_lstnew(&senv.new, sizeof(t_list_elem)));
	return (1);
}

int		c_cd(t_list *env, char *args[])
{
	t_cd	cd;

	if (ft_strcmp(args[0], "cd"))
		return (0);

	cd.home = get_data(env, "HOME");
	if (cd.home)
		if (args && args[1] && args[1][0] == '~')
			cd.path = ft_strjoin(cd.home, args[1] + 1);
		else if (args && args[1] && args[1][0] == '-'
				&& !args[1][1] && get_data(env, "OLDPWD"))
			cd.path = ft_strdup(get_data(env, "OLDPWD"));
		else if (args && args[1])
			cd.path = ft_strdup(args[1]);
		else
			cd.path = ft_strdup(cd.home);
	else
	{
		if (args && args[1])
			cd.path = ft_strdup(args[1]);
		else
		{
			ft_putendl("cd: path to HOME not found.");
			return (1);
		}
	}
	return (free_home_path(env, &cd) == 0);
}

int		ft_exit(char **args, int msg)
{
	if (!ft_strcmp(args[0], "exit"))
	{
		if (!args[1])
			exit(msg);
		else
			return (1);
	}
	else
		return (0);
}
