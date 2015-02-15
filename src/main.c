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

char	*get_path(t_list *env, char *bin)
{
	char		*path;
	char		**paths;
	char		**tmp;
	char		buff[1024];
	char		*ret;
	struct stat	stat_buff;

	path = get_data(env, "PATH");
	if (!path)
		return (bin);
	if (!stat(bin, &stat_buff))
		return (bin);
	paths = ft_strsplit(path, ':');
	tmp = paths;
	ret = NULL;
	while (tmp && *tmp)
	{
		ft_kebab(buff, *tmp, "/", bin, NULL);
		if (!stat(buff, &stat_buff))
		{
			printf("%s found at %s\n", bin, buff);
			ret = ft_strdup(buff);
			break ;
		}
		tmp++;
	}
	tmp = paths;
	while (tmp && *tmp)
		free(*tmp++);
	free(paths);
	return (ret);
}

char	**env_to_str(t_list *env)
{
	char		**strenv;
	t_list		*tmp;
	t_list_elem	*elem;
	int			i;

	tmp = env;
	strenv = (char**)ft_malloc((ft_lstlen(env) + 1));
	i = 0;
	while (tmp)
	{
		elem = tmp->content;
		strenv[i]= (char*)ft_malloc((ft_strlen(elem->key) + ft_strlen(elem->data) + 1));
		ft_kebab(strenv[i], elem->key, "=", elem->data, NULL);
		i++;
		tmp = tmp->next;
	}
	return (strenv);
}

int		c_env(t_list *env)
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

int		exec(char *bin, char **args, t_list *env)
{
	pid_t	father;
	char	**strenv;

	father = fork();
	if (father > 0)
		waitpid(father, NULL, 0);
	if (!father)
	{
		strenv = env_to_str(env);/*ho putin con, ca fuit fada!!*/
		execve(bin, args, strenv);
	}
	return (1);
}

void	prompt()
{
	ft_putstr("$> ");
}

int		command(char *line, t_list *env)
{
	char	*bin;
	char	**args;

	line = ft_strtrim(line);
	if (!line || !line[0])
		return (0);
	args = ft_strsplit(line, ' ');
	if (!args || !args[0] || !args[0][0])
		return (0);
	if (!ft_strcmp(args[0], "exit"))
	{
		ft_putendl("exit");
		exit(2);
	}
	else if (!ft_strcmp(args[0], "env"))
		return (c_env(env));
	bin = get_path(env, args[0]);
	if (bin == NULL)
		ft_putendl("Does not exist!");
	else if (exec(bin, args, env) == -1)
		ft_putendl("Error");
	return (0);
}

int		main(int argc, char *argv[], char *envp[])
{
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
	return(0);
}
