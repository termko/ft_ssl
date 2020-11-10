#include "main.h"

uint32_t	btol(uint32_t num)
{
	return (((num>>24)&0xff) |
			((num<<8)&0xff0000) |
			((num>>8)&0xff00) |
			((num<<24)&0xff000000));
}

void		ft_bzero(void *ptr, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		((char*)ptr)[i] = '\0';
		i++;
	}
}

char		*ft_realloc(char **str, char *tmp, int total, int got)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	ret = ft_strnew(total + got);
	while (i < total)
	{
		ret[i] = (*str)[i];
    	i++;
	}
	j = 0;
	while (j < got)
	{
		ret[i + j] = tmp[j];
		j++;
	}
	free(*str);
	return (ret);
}

long		ft_strlen(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return len;
}