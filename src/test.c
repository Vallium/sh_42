/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 12:15:04 by aalliot           #+#    #+#             */
/*   Updated: 2015/05/15 12:15:07 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/sh_1.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int		is_tab(char c)
{
	return (c == ' ' || c == '\t');
}

static int		word_len(char *str)
{
	int		i;

	i = -1;
	while (*str && !is_tab(*str))
	{
		if (*str == '\"')
		{
			i = i == -1 ? 0 : i;
			str++;
			while (*str != '\"' && *str)
			{
				str++;
				i++;
			}
		}
		else
			i++;
		str++;
	}
	return (i);
}

static int			word_count(char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (*str)
	{
		i = -1;
		while (*str && !is_tab(*str))
		{
			if (*str == '\"')
			{
				i = i == -1 ? 0 : i;
				str++;
				while (*str != '\"' && *str)
				{
					str++;
					i++;
				}
			}
			else
				i++;
			str++;
		}
		if (i > -1)
			nb++;
		if (is_tab(*str))
			str++;
	}
	return nb;
}

static char			*word_malloc(char **str)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = *str;
	while (**str && !is_tab(**str))
	{
		if (**str == '\"')
		{
			(*str)++;
			while (**str != '\"' && **str)
			{
				(*str)++;
				i++;
			}
		}
		else
			i++;
		(*str)++;
	}
	if (!(ret = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while(*tmp && i)
	{
		if (*tmp != '\"')
		{
			ret[j++] = *tmp;
			i--;
		}
		tmp++;
	}
	ret[j] = 0;
	return (ret);
}


char			**command_line_parser(char *line)
{
	char	**ret;
	char	**tmp;
	char	*tmp_line;
	int		nb;

	tmp_line = line;
	nb = word_count(line);
	if (!(ret = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	tmp = ret;
	while (*tmp_line)
	{
		if (word_len(tmp_line) > -1)
		{
			*tmp = word_malloc(&tmp_line);
			tmp++;
		}
		tmp_line++;
	}
	*tmp = 0;
	return (ret);
}

typedef struct		s_cmd
{
	char			*cmd_line;
	char			ope;
}					t_cmd;

t_cmd		*ope_chr(char **str)
{
	t_cmd	*ret;
	char	*tmp;
	char	*sub;

	tmp = *str;
	ret = (t_cmd*)malloc(sizeof(t_cmd));
	while (**str)
	{
		if (**str == '\"')
		{
			(*str)++;
			while (**str != '\"')
				(*str)++;
			(*str)++;
		}
		if (**str == '|')
			break;
		(*str)++;
	}
	ret->cmd_line = ft_strsub(tmp, 0, ft_strlen(tmp) - ft_strlen(*str));
	ret->ope = **str;
	(*str)++;
	return (ret);
}

int		main() {
	char	*line = " cat  	\"salut les gars\" |  \"\" et puis \"alors quoi\"sdad \" hel|lo \" he|in  \"sdfsdf\"  ";

	// char **tab = command_line_parser(line);

	// int		i;
	// for (i = 0; tab[i]; i++) {
	// 	printf("%s\n", tab[i]);
	// }
	t_cmd *cmd = ope_chr(&line);
	printf("%c : %s\n", cmd->ope, cmd->cmd_line);
	t_cmd	*test = ope_chr(&line);

	printf("%c : %s\n", test->ope, test->cmd_line);
		t_cmd	*test2 = ope_chr(&line);

		printf("%c : %s\n", test2->ope, test2->cmd_line);

	return 0;
}
