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

	if (args[1] != NULL)
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
	t_setenv	senv;

	senv.tmp = env;
	if (!args[1] || !args[1][0])
		return (0);
	if (args[2] && args[3])
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (0);
	}
	while (senv.tmp != NULL)
	{
		senv.elem = senv.tmp->content;
		if (!ft_strcmp(senv.elem->key, args[1]))
		{
			free(senv.elem->data);
			senv.elem->data = (args[2] ? ft_strdup(args[2]) : ft_strnew(1));
			return (0);
		}
		senv.tmp = senv.tmp->next;
	}
	senv.new.key = ft_strdup(args[1]);
	senv.new.data = args[2] ? ft_strdup(args[2]) : ft_strnew(1);
	ft_lstsmartpushback(&env, ft_lstnew(&senv.new, sizeof(t_list_elem)));
	return (0);
}

void	del_content(t_list *lst)
{
	t_list_elem	*elem;

	elem = lst->content;
	free(elem->data);
	free(elem->key);
	elem->data = NULL;
	elem->key = NULL;
}

void	del_test(void *content, size_t size)
{
	t_list_elem	*elem;

	elem = (t_list_elem*)content;
	free(elem->data);
	free(elem->key);
	elem->data = NULL;
	elem->key = NULL;
	(void)size;
}

int		c_unsetenv(t_list **env, char *args[])
{
	t_list	*current;
	t_list	*prev;
	t_list	*to_delete;
	t_list_elem *to_del;

	if (!args[1] || !args[1][0])
		return (0);
	while (*args)
	{
		current = *env;
		if (!ft_strcmp(((t_list_elem *)current->content)->key , *args))					// if premier
		{
			(*env) = (*env)->next;
			args++;
			free(((t_list_elem *)current->content)->data);
			free(((t_list_elem *)current->content)->key);
			free(current->content);
			free(current);
			continue ;
		}
		prev = current;
		current = current->next;
		while (current)
		{
			if (!ft_strcmp(((t_list_elem *)current->content)->key, *args))
			{
				if (!current->next)		// free tmp last
				{
					free(((t_list_elem *)current->content)->data);
					free(((t_list_elem *)current->content)->key);
					free(current->content);
					free(current);
					prev->next = NULL;
				}
				else
				{
					// stocke data a supprimer

					to_delete = current->next;
					to_del = current->content;

					current->content = current->next->content;
					current->content_size = current->next->content_size;
					current->next = current->next->next;

					free(to_del->data);
					free(to_del->key);
					free(to_del);
					free(to_delete);
				}
				break ;
			}
			prev = current;
			current = current->next;
		}
		args++;
	}
	return (0);
}

int		free_home_path(t_cd *cd)
{
	if (cd->path)
		free(cd->path);
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
	return (free_home_path(&cd));
}
