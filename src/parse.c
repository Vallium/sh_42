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

static int		is_tab(char c)
{
	return (c == ' ' || c == '\t');
}

static int		word_count(char *str)
{
	int		nbr;
	char	*tmp;

	nbr = 0;
	if (!is_tab(*str))
		nbr++;
	for (tmp = str ; *tmp; tmp++) {
		if (is_tab(*tmp) && !is_tab(*(tmp + 1)))
			nbr++, tmp++;
		if (*tmp == '"')
		{
			tmp++;
			while (*tmp != '"')
				tmp++;
		}
	}
	return (nbr);
}

static void		tab_fill(char **tab,char *str, int nb)
{
	int		nbr;
	char	*tmp;

	nbr = 0;
	if (!is_tab(*str))
		nbr++;
	for (tmp = str ; *tmp; tmp++) {
		if (is_tab(*tmp) && !is_tab(*(tmp + 1)))
			nbr++, tmp++;
		if (*tmp == '"')
		{
			tmp++;
			while (*tmp != '"')
				tmp++;
			tmp++;
		}
	}
}

static char			*wordlen(char **str)
{
	int i = 0;
	int j = 0;
	char *tmp = *str;
	while (**str && **str != '\t' && **str != ' ')
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
	if (i)
	{
		char *ret = malloc(i + 1);
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
	else
		return (0);
}

char			**command_line_parser(char *line)
{
	char	**ret;
	int		nb;

	nb = word_count(line);
	ret = (char**)malloc(sizeof(char*) * (nb + 1));
	tab_fill(ret, line, nb);
	return (ret);
}

int		main() {
	char	*line = " cat  	\"salut les gars\"  et puis \"alors quoi\"sdad \" hello \" hein  \"sdfsdf\"  ";

	char *str = line;
	char *tmp;
	int i;
	for (str = line; *str; str++)
	{
		if (tmp = wordlen(&str))
		{
			printf("%s\n", tmp);
		}
	}


	//printf("%d :%s\n", word_count(line), line);
	return 0;
}
