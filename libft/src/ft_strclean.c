//#include "libft.h"
#include <stdlib.h>

static unsigned int		ft_sp(char c)
{
	return (c == ' ' || c == '\t');
}

#include <stdio.h>

void				ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char*)s;
	while (n--)
		*str++ = 0;
}

char			*ft_strnew(size_t size)
{
	char		*str;

	str = (char*)malloc(sizeof(char) * (size));
	if (!str)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}

size_t			ft_strlen(const char *s)
{
	size_t		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char			*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char		*dst;
	char		*ret;

	if (!len)
		return ("");
	if (!s || !*s)
		return (NULL);
	dst = (char*)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ret = dst;
	while (len--)
		*dst++ = s[start++];
	*dst = 0;
	return (ret);
}


char					*ft_strtrim(char *s)
{
	char				*dst;
	char				*tmp;
	int					i;
	int					e;

	tmp = s;
	if (!s)
		return (NULL);
	i = 0;
	while (ft_sp(*s++))
		i++;
	s -= i + 1;
	e = ft_strlen(s) - 1;
	if (!*s || e == i - 1)
	{
		free(tmp);
		return (dst = ft_strnew(1));
	}
	if (i != (e + 1))
		while (ft_sp(s[e]))
			e--;
	dst = ft_strsub(s, i, (e - i + 1));
	free(tmp);
	return (dst);
}

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
	printf("%d\n", cnt);

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
	printf("%s\n", ret);
	return (ret);
}

int		main(int argc, char **argv)
{
	(void)argc;

	argv[1] = ft_strclean(argv[1]);
	return 0;
}
