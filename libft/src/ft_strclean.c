//#include "libft.h"
#include <stdlib.h>

static unsigned int		ft_sp(char c)
{
	return (c == ' ' || c == '\t');
}

#include <stdio.h>

char					*ft_strclean(char *str)
{
	char	*tmp;
	char	*ret;
	int		cnt;

	cnt = 0;
	tmp = str;
	while (*tmp)
	{
		if (!ft_sp(*tmp))
			cnt++, tmp++;
		else if (ft_sp(*tmp) && !ft_sp(*tmp + 1))
			cnt++, tmp++;
		else if (ft_sp(*tmp))
			tmp++;
	}
	printf("%d\n", cnt);
	ret = NULL;
	return (ret);
}

int		main(int argc, char **argv)
{
	(void)argc;

	argv[1] = ft_strclean(argv[1]);
	return 0;
}
