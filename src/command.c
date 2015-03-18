/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 12:56:17 by adoussau          #+#    #+#             */
/*   Updated: 2015/02/17 12:56:19 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_1.h"

int		line_trim(char **line)
{
	*line = ft_strclean(*line);
	if (!*line || !*line[0])
		return (0);
	return (1);
}

void	args_filter(t_list *env, char **args, char *line)
{
	int		i;

	i = 0;
	(void)line;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "~"))
		{
			free(args[i]);
			args[i] = ft_strdup(get_data(env, "HOME"));
		}
		i++;
	}
}

int		command(char *line, t_list **env)
{
	t_command	t;

	if (!line_trim(&line))
		return (magic_free(line));
	t.args = ft_strsplit(line, ' '), args_filter(*env, t.args, line);
	if (!t.args || !t.args[0] || !t.args[0][0])
		return (magic_free(line));
	t.bin = get_path(*env, t.args[0]);
	if (!ft_strcmp(t.args[0], "exit"))
		ft_exit(t.args, 0);
	else if (!ft_strcmp(t.args[0], "cd"))
		c_cd(*env, t.args);
	else if ((!ft_strcmp(t.args[0], "env") || !ft_strcmp(t.args[0], "setenv"))
			&& !t.args[1])
		c_env(*env, t.args);
	else if (ft_strcmp(t.args[0], "unsetenv") == 0)
		c_unsetenv(env, t.args);
	else if (ft_strcmp(t.args[0], "setenv") == 0)
		c_setenv(env, t.args);
	else if (t.bin == (char*)1)
		print_error(1, t.args[0]);
	else if (t.bin == NULL || exec(t.bin, t.args, *env) == -1)
		print_error(2, t.args[0]);
	return (command_free(t.args, line, t.bin));
}

int		exec(char *bin, char *args[], t_list *env)
{
	pid_t			father;
	char			**strenv;
	struct stat		stat_buff;

	lstat(bin, &stat_buff);
	if (!(stat_buff.st_mode & 010) | S_ISDIR(stat_buff.st_mode))
		return (print_error(1, bin));
	if (!S_ISREG(stat_buff.st_mode) || !(stat_buff.st_mode & 1))
		return (print_error(2, bin));
	if (!ft_strchr(bin, '/'))
		return (-1);
	father = fork();
	if (father > 0)
		waitpid(father, NULL, 0);
	if (!father)
	{
		strenv = env_to_str(env);
		signal(SIGINT, SIG_DFL);
		if (execve(bin, args, strenv) < 0)
		{
			ft_putstr("ft_minishell1: exec format error: ");
			ft_putendl_fd(bin, 2);
			exit(2);
		}
	}
	return (1);
}

int		print_error(int ind, char *args)
{
	if (ind == 1)
	{
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": permission denied.", 2);
	}
	else if (ind == 2)
	{
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": command not found.", 2);
	}
	else if (ind == 3)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(args, 2);
	}
	return (0);
}
