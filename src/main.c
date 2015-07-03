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

void		run_pipe (char **args1, char **args2, t_list *env) {
	int const	READ_END = 0;
	int const	WRITE_END = 1;
	pid_t		child = -1;
	int		pdes[2];
	char	*bin1;
	char	*bin2;
	char	**strenv;

	bin1 = get_path(env, args1[0]);
	bin2 = get_path(env, args2[0]);
	strenv = env_to_str(env);

	pipe(pdes);

	printf("bin1 = %s,  bin2 = %s\n",bin1, bin2);

	child = fork();

	switch ((int)child) {
		case -1:
			close(pdes[READ_END]);
			close(pdes[WRITE_END]);
			perror("error");
		case 0:
		signal(SIGINT, SIG_DFL);
			dup2(pdes[WRITE_END], STDOUT_FILENO);
			close(pdes[READ_END]);
			wait(NULL);
			execve(bin1, args1, strenv);					// cas bin1
			perror("error");
			break;
	}
	signal(SIGINT, SIG_DFL);
	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
	wait(NULL);
	execve(bin2, args2, strenv);							// cas bin2
}

void		pipe_cmd(char **cmd1, char **cmd2, t_list **env)
{
	pid_t	child = -1;

	// printf("1->%s\n2->%s\n", bin1, bin2);
	child = fork();

	switch ((int)child) {
		case -1:
			perror("error");
			break;
		case 0:
			run_pipe(cmd1, cmd2, *env);
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
	t_cmd2		*data_tmp2;

	data = command_line_parser(line);
	tmp = data;


		while(tmp)
		{
			data_tmp = (t_cmd2 *)tmp->content;
			if (data_tmp->ope == ';' || !data_tmp->ope)
				command(data_tmp->tab, env);
			else if (data_tmp->ope == '|')
			{
				tmp = tmp->next;
				data_tmp2 = (t_cmd2 *)tmp->content;
				pipe_cmd(data_tmp->tab, data_tmp2->tab, env);
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
		ft_putstr("$> ");
		//prompt(env);
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
