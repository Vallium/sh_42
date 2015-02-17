#include <stdio.h>
#include <stdlib.h>
#include "includes/libft.h"

int     main()
{
char    *line;

	int fd = open("README.md",'r');

    while (get_next_line(fd, &line))
        printf("[%s]\n",line);
    get_next_line(fd, &line);
    printf("[%s]\n",line);
    return 0;
}
