
#include <stdio.h>
#include <stdlib.h>
#include "includes/libft.h"

int     main()
{
char    *line;

    while (get_next_line(0, &line))
    {
        printf("[%s]\n",line);
    }


    return 0;
}
