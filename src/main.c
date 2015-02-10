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

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

//#define BUFF_SIZE 1024

int		main(int argc, char *argv[])
{
	char	*args;
	char	**ex;
	int		ret;
	pid_t	father;


	(void)argc;
	(void)argv;
	args = NULL;
	while(42)
	{
		father = fork();
		if (father > 0)
		{
			waitpid(father, NULL, 0);
		}
		if (father == 0)
		{
			ft_putstr("$> ");
			while ((ret = get_next_line(0, &args)))
			{
				ex = ft_strsplit(args, ' ');
				execve("/bin/ls", ex, NULL);
			}
		}
	}
	return(0);
}
