#include "libft.h"
#include <stdlib.h>

static unsigned int		ft_sp(char c)
{
	return (c == ' ' || c == '\t');
}

// #include <stdio.h>

char					*ft_strclean(char *str)
{
	char	*tmp;
	char	*ret;
	char	*tmp_ret;
	int		cnt;

	cnt = 0;
	tmp = str;
	while (*tmp)
	{
		if (!ft_sp(*tmp))
			cnt++, tmp++;
		else if (ft_sp(*tmp) && !ft_sp(*(tmp + 1)))
			cnt++, tmp++;
		else if (ft_sp(*tmp))
			tmp++;
	}
	cnt++;
	// printf("%d\n", cnt);

	ret = (char*)malloc(sizeof(char) * cnt);

	tmp = str;
	tmp_ret = ret;

	while (*tmp)
	{
		if (!ft_sp(*tmp))
		{
			*tmp_ret = *tmp;
			tmp++;
			tmp_ret++;
		}
		else if (ft_sp(*tmp) && !ft_sp(*(tmp + 1)))
		{
			*tmp_ret = ' ';
			tmp++;
			tmp_ret++;
		}
		else if (ft_sp(*tmp))
			tmp++;
	}
	*tmp_ret = 0;
	ret = ft_strtrim(ret);
	// printf("%s\n", ret);
	return (ret);
}

// int		main(int argc, char **argv)
// {
// 	(void)argc;
//
// 	argv[1] = ft_strclean(argv[1]);
// 	return 0;
// }
