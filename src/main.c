/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:54:57 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/02 11:56:00 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_1.h"
#include <stdio.h>

t_list	*get_env(char *envp[])
{
	t_list_elem	elem;
	t_list		*env;
	char		**tmp;
	char		*chr;

	env = NULL;
	tmp = envp;
	while(tmp && *tmp)
	{
		chr = ft_strchr(*tmp, '=');
		elem.key = ft_strsub(*tmp, 0, chr - *tmp);
		elem.data = ft_strdup(chr + 1);
		ft_lstpushback(&env, ft_lstnew(&elem, sizeof(t_list_elem)));
//		printf("%s=%s\n", elem.key, elem.data);
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

//char	*get_path(t_list *env, char *bin)
//{
//	char		*path;
//	char		**paths;
//	char		**tmp;
//	char		buff[1024];
//	struct stat	stat_buff;
//
//	path = get_data(env, "PATH");
//	if (!path)
//		return (bin);
//	paths = ft_strsplit(path, ':');
//	if (!stat(bin, &stat_buff))
//		return (bin);
//	tmp = paths;
//	while (tmp && *tmp)
//	{
//		ft_kebab(buff)
//	}
//	return (NULL);
//}

int		print_env(t_list *env)
{
	t_list		*tmp;
	t_list_elem	*elem;

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

void	prompt()
{
	ft_putstr("$> ");
}

int		command(char *line, t_list *env)
{
	char	*cmd;

	if (!ft_strchr(line, ' '))
		cmd = ft_strdup(line);
	else
		cmd = ft_strsub(line, 0, ft_strchr(line, ' ') - line);
	if (!ft_strcmp(cmd, "exit"))
	{
		ft_putendl("exit");
		exit(2);
	}
	else if (!ft_strcmp(cmd, "env"))
		return (print_env(env));
	return (0);
}

int		main(int argc, char *argv[], char *envp[])
{
//	char	*args;
//	char	**ex;
//	int		ret;
//	pid_t	father;
	t_list	*env;
	char	*line;

	(void)argc;
	(void)argv;
	env = get_env(envp);

	while (42)
	{
		prompt();
		get_next_line(0, &line);
		command(line, env);
	}
//	args = NULL;
//	while(42)
//	{
//		father = fork();
//		if (father > 0)
//		{
//			waitpid(father, NULL, 0);
//		}
//		if (father == 0)
//		{
//			ft_putstr("$> ");
//			while ((ret = get_next_line(0, &args)))
//			{
//				ex = ft_strsplit(args, ' ');
//				execve("/bin/ls", ex, NULL);
//			}
//		}
//	}
	return(0);
}
