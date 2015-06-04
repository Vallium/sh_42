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

void		run_pipe (void) {
	int const	READ_END = 0;
	int const	WRITE_END = 1;
	pid_t		child = -1;
	int		pdes[2];

	char	*cmd1 = NULL;
	char	*cmd2 = NULL;
	char	*args1[3];
	char	*args2[3];

	cmd1 = "/bin/ls";
	args1[0] = cmd1;
	args1[1] = "-lf";
	args1[2] = NULL;

	cmd2 = "/bin/cat";
	args2[0] = cmd2;
	args2[1] = "-e";
	args2[2] = NULL;

	pipe(pdes);

	child = fork();

	switch ((int)child) {
		case -1:
			close(pdes[READ_END]);
			close(pdes[WRITE_END]);
			perror("error");
		case 0:
			dup2(pdes[WRITE_END], STDOUT_FILENO);
			close(pdes[READ_END]);
			execve(cmd1, args1, NULL);
			perror("error");
			break;
	}

	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
	wait(NULL);
	execve(cmd2, args2, NULL);
}

void		pipe_cmd(char **cmd, t_list **env)
{
	pid_t	child = -1;
	char	*bin;

	// bin = get_path(cmd[0], )
	child = fork();

	switch ((int)child) {
		case -1:
			perror("error");
			break;
		case 0:
			run_pipe();
			perror("error");
			break;
	}
	wait(NULL);
}

void		interpret(char *line, t_list **env)
{
	t_list		*data;
	t_list		*tmp;
	t_cmd2		*data_tmp;

	data = command_line_parser(line);
	tmp = data;


		while(tmp)
		{
			data_tmp = (t_cmd2 *)tmp->content;
			if (data_tmp->ope == ';' || !data_tmp->ope)
				command(data_tmp->tab, env);
			else if (data_tmp->ope == '|')
			{
				pipe_cmd(data_tmp->tab, env);
				tmp = tmp->next;
			}
			else
				ft_putendl("other ope");
			tmp = tmp->next;
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
		prompt(env);
		if (!get_next_line(0, &line))
		{
			ft_putendl("exit");
			return (0);
		}
		// printf("<<%s>>\n", line);
		interpret(line, &env);
		// command(line, &env);
	}
	return (0);
}
