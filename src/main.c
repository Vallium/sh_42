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

void	prompt(t_list *env)
{
	char	*user;
	char	*home;
	char	*pwd;

	pwd = GET_CWD;
	user = get_data(env, "USER");
	home = get_data(env, "HOME");
	ft_putchar('\033');
	ft_putstr("[36m• ");
	if (user)
		ft_putstr(user);
	else
		ft_putstr("Vallium");
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
	ft_putstr("[39m » ");
	free(pwd);
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
		get_next_line(0, &line);
		command(line, &env);
	}
	return (0);
}
