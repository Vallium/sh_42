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

void	get_env(t_list *env, char *envp[])
{
	t_list_elem	elem;
	char		**tmp;
	char		*chr;

	tmp = envp;
	while(tmp && *tmp)
	{
		chr = ft_strchr(*tmp, '=');
		elem.key = ft_strsub(*tmp, 0, chr - *tmp);
		elem.data = ft_strdup(chr + 1);
		ft_lstadd(&env, ft_lstnew(&elem, sizeof(t_list_elem)));
//		printf("%s=%s\n", elem.key, elem.data);
		tmp++;
	}
}

void	test(char *envp[])
{
	int	i;

	printf("env :\n");
	for(i=0; envp[i] ;i++)
		printf("%s\n",envp[i]);
}

void	prompt()
{
	ft_putstr("$> ");
}

int		command(char *line)
{
	if (!ft_strcmp(line, "exit"))
	{
		ft_putendl("exit");
		exit(2);
	}
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
//	test(envp);
	env = NULL;
	get_env(env, envp);

	while (42)
	{
		prompt();
		get_next_line(0, &line);
		command(line);
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
