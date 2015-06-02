/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 11:54:57 by adoussau          #+#    #+#             */
/*   Updated: 2015/02/20 20:06:18 by adoussau         ###   ########.fr       */
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

void		interpret(char *line, t_list **env)
{
	t_list		*data;

	data = command_line_parser(line);
	(void)env;
		// t_list	*lst;

		// lst = command_line_parser(line);


		t_list *tmp = data;
		t_cmd2	*data2;

		while(tmp)
		{
			data2 = (t_cmd2 *)tmp->content;
			int i = 0;
			while (data2->tab[i])
			{
				printf("tab[%d] = [%s]\n", i, data2->tab[i]);
				i++;
			}
			printf("opt = {%c}\n\n", data2->ope);
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
		printf("<<    |%s|    >>\n", line);
		interpret(line, &env);
		// command(line, &env);
	}
	return (0);
}
