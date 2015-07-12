/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:54:57 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/20 20:06:18 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_1.h"

void	prompt(t_list *env)
{
	char	*user;
	char	*home;
	char	*pwd;

	pwd = GET_CWD;
	user = get_data(env, "USER");
	home = get_data(env, "HOME");
	ft_putchar('\033');
	ft_putstr("[36m# ");
	if (user)
		ft_putstr(user);
	else
		ft_putstr("Unknown");
	ft_putchar('\033');
	ft_putstr("[39m in ");
	ft_putchar('\033');
	ft_putstr("[33m");
	if (home && ft_strstr(pwd, home))
		ft_putchar('~'),
		ft_putstr(ft_strstr(pwd, home) + ft_strlen(home));
	else
		ft_putstr(pwd);
	ft_putchar('\033');
	ft_putstr("[39m $ ");
	free(pwd);
}

#include <stdio.h>

int		exec_test(char *bin, char *args[], t_list *env)
{
	char			**strenv;
	struct stat		stat_buff;

	lstat(bin, &stat_buff);
	if (!(stat_buff.st_mode & 010) | S_ISDIR(stat_buff.st_mode))
		dprintf(2, "permission denied 2 = %s\n", bin), exit(2);
	if (!ft_strchr(bin, '/') || bin == NULL)
		dprintf(2, "command not found = %s\n", bin), exit(2);
	if (!S_ISREG(stat_buff.st_mode) || !(stat_buff.st_mode & 1))
		dprintf(2, "permission denied 1 = %s\n", bin), exit(2);

	strenv = env_to_str(env);
	signal(SIGINT, SIG_DFL);
	if (execve(bin, args, strenv) < 0)
	{
		ft_putstr("ft_minishell2: exec format error: ");
		ft_putendl_fd(bin, 2);
		exit(2);
	}

	return (1);
}

void		pipe_cmd(t_list **tmp, t_list *env) {
	int			fd_in;
	pid_t		child;
	int			pdes[2];
	char		*bin;
	int			file;
	t_cmd2		*data_tmp;
	t_cmd2		*data_tmp2;

	fd_in = 0;
	data_tmp = (t_cmd2 *)(*tmp)->content;
	while (*tmp) {
		data_tmp = (t_cmd2 *)(*tmp)->content;
		if ((bin = get_path(env, data_tmp->tab[0])) == (char*)1) {
			dprintf(2, "Permission denied %s\n", data_tmp->tab[0]);		// Message a modifier
			*tmp = (*tmp)->next;
			continue;
		}
		if ((*tmp)->next && (data_tmp->ope == '>' || data_tmp->ope == '?')) {
			data_tmp2 = (t_cmd2 *)(*tmp)->next->content;
			*tmp = (*tmp)->next;
		}
		pipe(pdes);		// create pipe
		if ((child = fork()) == -1) {
			ft_putstr_fd("Fork Error\n", 2);
		}
		else if (child == 0) {
			dup2(fd_in, 0);
			if ((*tmp)->next && data_tmp->ope == '|')
				dup2(pdes[1], 1);
			else if (data_tmp->ope == '>') {
				file = open(data_tmp2->tab[0], O_RDWR | O_CREAT, 0644);
				dup2(file, 1);
			}
			else if (data_tmp->ope == '?') {
				file = open(data_tmp2->tab[0], O_RDWR | O_CREAT | O_APPEND, 0644);
				dup2(file, 1);
			}
			close(pdes[0]);
			exec_test(bin, data_tmp->tab, env);
		}
		else {
			wait(NULL);
			close(pdes[1]);
			fd_in = pdes[0];
			*tmp = (*tmp)->next;
		}
	}
}

void		interpret(char *line, t_list **env)
{
	t_list		*data;
	t_list		*tmp;
	t_cmd2		*data_tmp;

	data = command_line_parser(line);
	tmp = data;

		while (tmp)
		{
			data_tmp = (t_cmd2 *)tmp->content;
			if (data_tmp->ope == ';' || !data_tmp->ope) {
				command(data_tmp->tab, env);
				tmp = tmp->next;
				// pipe_cmd(&tmp, *env);
			}
			else if (data_tmp->ope == '|' || data_tmp->ope == '>' || data_tmp->ope == '?')
				pipe_cmd(&tmp, *env);
			else {
				ft_putendl("other ope");
				tmp = tmp->next;
			}
		}
}

int		main(int argc, char *argv[], char *envp[])
{
	t_list	*env;
	char	*line;

	(void)argc;
	(void)argv;
	signal(SIGINT, SIG_IGN);
	env = get_env(envp);
	while (42)
	{
		ft_putstr("$> ");
		//prompt(env);
		if (!get_next_line(0, &line))
		{
			ft_putendl("exit");
			return (0);
		}
		interpret(line, &env);
		// command(line, &env);
	}
	return (0);
}
