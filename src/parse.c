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

#include "sh_1.h"

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
