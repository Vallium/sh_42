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

char	*get_path(t_list *env, char *bin)//ca fuit ici
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
			if (!(stat_buff.st_mode & 1))
				ret = (char*)1;
			else
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
	int			size;

	tmp = env;
	size = ft_lstlen(env);
	strenv = (char**)ft_malloc(sizeof(char*) * (size + 1));
	i = 0;
	while (tmp)
	{
		elem = tmp->content;
		//strenv[i]= (char*)ft_malloc((ft_strlen(elem->key) + ft_strlen(elem->data) + 2));
		//ft_kebab(strenv[i], elem->key, "=", elem->data, NULL);
		strenv[i] = ft_burger(elem->key, '=', elem->data);
		i++;
		tmp = tmp->next;
	}
	strenv[i] = NULL;
	return (strenv);
}

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
		if (!ft_strcmp(elem->key, args[1]))
		{
			elem->data = args[2];
			return(0);
		}
		tmp = tmp->next;
	}
	new.key = args[1];
	new.data = args[2] ? args[2] : "";
	ft_lstsmartpushback(&env, ft_lstnew(&new, sizeof(t_list_elem)));
	return (0);
}

int		c_unsetenv(t_list **env, char *args[])
{
	t_list			**tmp;
	t_list			*last;
	t_list_elem		*elem;
	int				i;

	tmp = env;
	i = 1;
	last = NULL;
	if (!args[1] || !args[1][0])
		return (0);
	while (args[i++])
	{
		while (*tmp)
		{
			elem = (*tmp)->content;
			if (!ft_strcmp(elem->key, args[i - 1]))
			{
				if (!(*tmp)->next)
					last->next = NULL;
				else
					ft_lstdelnode(tmp);
				break ;
			}
			last = *tmp;
			*tmp = (*tmp)->next;
		}
	}
	return (0);
}

int		c_cd(t_list *env, char *args[])
{
	char	*path;
	char	*home;

	home = get_data(env, "HOME");
	if (home)
	{
		if (args && args[1] && args[1][0] == '~')
			path = ft_strjoin(home, args[1] + 1);
		else if (args && args[1])
			path = ft_strdup(args[1]);
		else
			path = ft_strdup(home);
	}
	else
	{
		if (args && args[1])
			path = ft_strdup(args[1]);
		else
		{
			ft_putendl("Home error");
			return (0);
		}
	}
	if (chdir(path))
	{
		ft_putstr("cd: no such file or directory:");
		ft_putendl(path);
	}
	return (0);
}

int		exec(char *bin, char *args[], t_list *env)
{
	pid_t	father;
	char	**strenv;

	if (!ft_strchr(bin, '/'))
		return (-1);
	father = fork();
	if (father > 0)
		waitpid(father, NULL, 0);
	if (!father)
	{
		strenv = env_to_str(env); /*ho putin con, ca fuit fada!!*/
		execve(bin, args, strenv);
	}
	return (1);
}

void	prompt(t_list *env)
{
	char	*user;
//	char	*pwd;

	user = get_data(env, "USER");
//	pwd = get_data(env, "PWD");
	ft_putchar('\033');
	ft_putstr("[36m# ");
	ft_putstr(user);
//	ft_putchar('\033');
//	ft_putstr("[39m");
//	ft_putstr(" in ");
//	ft_putchar('\033');
//	ft_putstr("[33m");
//	ft_putstr(pwd);
	ft_putstr(" $ ");
	ft_putchar('\033');
	ft_putstr("[39m");}

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
	else if (!ft_strcmp(args[0], "cd"))
		return (c_cd(env, args));
	else if (!ft_strcmp(args[0], "env") || (!ft_strcmp(args[0], "setenv") && !args[1]))
		return (c_env(env, args));
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		return (c_unsetenv(&env, args));
	else if (ft_strcmp(args[0], "setenv") == 0)
		return (c_setenv(env, args));
	bin = get_path(env, args[0]);
	if (bin == NULL)
	{
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": Command not found.", 2);
	}
	else if (bin == (char*)1)
	{
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": Permission denied.", 2);
	}
	else if (exec(bin, args, env) == -1)
	{
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": Command not found.", 2);
	}
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
		prompt(env);
		get_next_line(0, &line);
		command(line, env);
//		ft_putchar('\n');
	}
	return(0);
}
