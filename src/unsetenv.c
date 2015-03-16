/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 15:12:07 by adoussau          #+#    #+#             */
/*   Updated: 2015/02/19 15:12:09 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh_1.h>

void	unsetenv_first(t_list **env, t_list *current)
{
	(*env) = (*env)->next;
	free(((t_list_elem *)current->content)->data);
	free(((t_list_elem *)current->content)->key);
	free(current->content);
	free(current);
}

void	free_mid_node(t_usenv *usenv)
{
	usenv->to_delete = usenv->current->next;
	usenv->to_del = usenv->current->content;
	usenv->current->content = usenv->current->next->content;
	usenv->current->content_size = usenv->current->next->content_size;
	usenv->current->next = usenv->current->next->next;
	free(usenv->to_del->data);
	free(usenv->to_del->key);
	free(usenv->to_del);
	free(usenv->to_delete);
}

void	unsetenv_rest(t_usenv *usenv, char *args)
{
	while (usenv->current)
	{
		if (!ft_strcmp(((t_list_elem *)usenv->current->content)->key, args))
		{
			if (!usenv->current->next)
			{
				free(((t_list_elem *)usenv->current->content)->data);
				free(((t_list_elem *)usenv->current->content)->key);
				free(usenv->current->content);
				free(usenv->current);
				usenv->prev->next = NULL;
			}
			else
				free_mid_node(usenv);
			break ;
		}
		usenv->prev = usenv->current;
		usenv->current = usenv->current->next;
	}
}

int		c_unsetenv(t_list **env, char *args[])
{
	t_usenv	usenv;

	if (!args[1] || !args[1][0])
	{
		ft_putendl_fd("unsetenv: too few arguments.", 2);
		return (0);
	}
	while (*args)
	{
		usenv.current = *env;
		if (!ft_strcmp(((t_list_elem *)usenv.current->content)->key, *args))
		{
			unsetenv_first(env, usenv.current);
			args++;
			continue ;
		}
		usenv.prev = usenv.current;
		usenv.current = usenv.current->next;
		unsetenv_rest(&usenv, *args);
		args++;
	}
	return (0);
}
