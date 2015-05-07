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

//char		**command_line_parser(char *line)
//{
//	char	**ret;
//
//	return (ret);
//}

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

int		main() {
	char	*line = "cat  	\"salut les gars\"  et puis \"alors quoi\" hein";

	printf("%d :%s\n", word_count(line), line);
	return 0;
}
