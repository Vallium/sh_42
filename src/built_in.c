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

	if (args[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (0);
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
	return (0);
}

int		c_setenv(t_list *env, char *args[])
{
	t_list			*tmp;
	t_list_elem		*elem;
	t_list_elem		new;

	tmp = env;
	if (!args[1] || !args[1][0])
		return (0);
	if (args[3])
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (0);
	}
	while (tmp != NULL)
	{
		elem = tmp->content;
		if (!ft_strcmp(elem->key, args[1]) && (elem->data = args[2]))
			return (0);
		tmp = tmp->next;
	}
	new.key = args[1];
	new.data = args[2] ? args[2] : "";
	ft_lstsmartpushback(&env, ft_lstnew(&new, sizeof(t_list_elem)));
	return (0);
}

int		c_unsetenv(t_list **env, char *args[])
{
	t_usetenv	usenv;

	usenv.tmp = env;
	usenv.i = 1;
	usenv.last = NULL;
	if (!args[1] || !args[1][0])
		return (0);
	while (args[usenv.i++])
	{
		while (*usenv.tmp)
		{
			usenv.elem = (*usenv.tmp)->content;
			if (!ft_strcmp(usenv.elem->key, args[usenv.i - 1]))
			{
				if (!(*usenv.tmp)->next)
					usenv.last->next = NULL;
				else
					ft_lstdelnode(usenv.tmp);
				break ;
			}
			usenv.last = *usenv.tmp;
			*usenv.tmp = (*usenv.tmp)->next;
		}
	}
	return (0);
}

int		c_cd(t_list *env, char *args[])
{
	t_cd	cd;

	cd.home = get_data(env, "HOME");
	if (cd.home)
	{
		if (args && args[1] && args[1][0] == '~')
			cd.path = ft_strjoin(cd.home, args[1] + 1);
		else if (args && args[1])
			cd.path = ft_strdup(args[1]);
		else
			cd.path = ft_strdup(cd.home);
	}
	else
	{
		if (args && args[1])
			cd.path = ft_strdup(args[1]);
		else
		{
			ft_putendl("Home error");
			return (0);
		}
	}
	if (chdir(cd.path))
		print_error(3, cd.path);
	return (0);
}
