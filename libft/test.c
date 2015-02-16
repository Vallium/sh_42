/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str;

	while (get_next_line(0, &str))
	{
		printf("%s\n",str);
		free(str);
	}

	while(42);
}
