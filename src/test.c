/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 12:15:04 by aalliot           #+#    #+#             */
/*   Updated: 2015/06/01 07:45:54 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_1.h"
// #include "libft.h"
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
			i = i == -1 ? 1 : i + 1;
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
	// printf("len: %d\n", i);
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


char			**parser(char *line)
{
	char	**ret;
	char	**tmp;
	char	*tmp_line;
	int		nb;

	tmp_line = line;
	nb = word_count(line);
	// printf("wdnb = %d\n",nb);
	if (!(ret = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	tmp = ret;
	while (*tmp_line)
	{

		if (word_len(tmp_line) > -1)
		{
			// printf("len: %d\n", word_len(tmp_line));
			*tmp = word_malloc(&tmp_line);
			tmp++;
		}
		tmp_line++;
	}
	*tmp = 0;
	return (ret);
}

// typedef struct		s_cmd2
// {
// 	char			**tab;
// 	char			ope;
// }					t_cmd2;
//
// typedef struct		s_cmd
// {
// 	char			*cmd_line;
// 	char			ope;
// }					t_cmd;

t_cmd		ope_chr(char **str)
{
	t_cmd	ret;
	char	*tmp;
	int		dec;

	tmp = *str;
	dec = 0;
	while (**str)
	{
		if (**str == '\"')
		{
			(*str)++;
			while (**str != '\"')
				(*str)++;
			(*str)++;
		}
		if (**str == '|' || **str == ';')
			break;
		if (**str == '>')
		{
			dec = *(*str + 1) == '>' ? 1 : 0;
			break;
		}
		if (**str == '<')
		{
			dec = *(*str + 1) == '<' ? 1 : 0;
			break;
		}
		(*str)++;
	}
	ret.cmd_line = ft_strsub(tmp, 0, ft_strlen(tmp) - ft_strlen(*str));
	ret.ope = dec ? **str + 1 : **str;
	(*str) += dec ? 2 : 1;
	return (ret);
}

t_list			*command_line_parser(char *line)
{
	t_list		*lst;
	t_cmd		cmd;
	t_cmd2		cmd2;
	// char		**tmp;

	lst = NULL;
	while (*line)
	{
		cmd = ope_chr(&line);
		cmd2.tab = parser(cmd.cmd_line);
		cmd2.ope = cmd.ope;
		ft_lstsmartpushback(&lst, ft_lstnew(&cmd2, sizeof(t_cmd2)));
		if (!cmd2.ope)
			break;
		free(cmd.cmd_line);
	}
	return(lst);
}

// int		main() {
// 	char	*line = "cat -e \"salut\"";
//
// 	// printf("%s\n%d\n", line, word_len(line));
//
// 	t_list	*lst;
//
// 	lst = command_line_parser(line);
//
//
// 	t_list *tmp = lst;
// 	t_cmd2	*data;
//
// 	while(tmp)
// 	{
// 		data = (t_cmd2 *)tmp->content;
// 		int i = 0;
// 		while (data->tab[i])
// 		{
// 			printf("tab[%d] = [%s]\n", i, data->tab[i]);
// 			i++;
// 		}
// 		printf("opt = {%c}\n\n", data->ope);
// 		tmp = tmp->next;
// 	}
//
// 	return 0;
// }
