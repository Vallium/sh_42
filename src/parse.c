/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 11:18:34 by aalliot           #+#    #+#             */
/*   Updated: 2015/05/07 11:18:40 by aalliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "sh_1.h"

#include <string.h>

static int		is_tab(char c)
{
	return (c == ' ' || c == '\t');
}

char			is_cmd(char str)
{
	return (str == '|');
}

static int		word_len(char *str)
{
	int		i;

	i = -1;

	/*if is_cmd(str)
		return (-2);*/
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
			else if (is_cmd(*str))
			{
				nb++;
				str++;
				break;
			}
			else
			{
				i++;
			}
			str++;
		}
		if (i > -1)
			nb++;
		if (is_tab(*str))
			str++;
	}
	return nb;
}

static char			*word_malloc(char **str, int *cmd)
{
	int		i;
	int		j;
	char	*ret;
	char	*tmp;

	*cmd = 0;

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
		else if (is_cmd(**str))
		{
			*cmd = '|';
			break;
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


typedef struct s_test
{
	char	type;
	char	*data;
}			t_test;

t_test			*command_line_parser(char *line)
{
	t_test		*ret;
	t_test		*tmp;
	char	*tmp_line;
	int		nb;
	int 	cmd;

	tmp_line = line;
	nb = word_count(line);

	printf("nb : %d\n",nb);

	if (!(ret = (t_test*)malloc(sizeof(t_test) * (nb))))
		return (NULL);
	tmp = ret;
	while (*tmp_line)
	{
		if (word_len(tmp_line) > -1)
		{
			tmp->type = 'w';
			tmp->data = word_malloc(&tmp_line, &cmd);
			if (cmd == '|')
			{
				tmp++;
				tmp->type = '|';
				tmp->data = 0;
			}
			tmp++;
		}
		tmp_line++;
	}
	return (ret);
}

 int		main() {
 	char	*line = " cat  	\"salut les gars\"  \"\" et  cat\"|\"grep puis \"alors quoi\"sdad \" hello \" hein  \"sdfsdf\"  ";

 	t_test *tab = command_line_parser(line);

	int i = 0;

	for (;i < 10;i++)
	{
		printf("%c : %s\n", tab[i].type, tab[i].data);
	}

 	return 0;
 }
