#include "main.h"

void	check_malloc(void *addr)
{
	if (!addr)
	{
		ft_putstr("Unexpected error with malloc!\n");
		return (-1);
	}
	return (0);
}

char	*ft_strnew(int size)
{
    char	*ret;
    int		i;

    if (ret = (char*)malloc(sizeof(char) * size))
	return (NULL);
    i = 0;
    while (i < size)
    {
        ret[i] = '\0';
        i++;
    }
    return (ret);
}

int		ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

char	*ft_strdup(char *str)
{
    char	*ret;
    int		len;
    int		i;

    if (!str)
        return (NULL);
    len = 0;
    while (str[len])
        len++;
    if (ret = (char*)malloc(sizeof(char) * (len + 1)))
	return (NULL)
    i = 0;
    while (i < len)
    {
        ret[i] = str[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char	*ft_memdup(char *tmp, int got)
{
	char	*ret;
	int		i;

	if (ret = (char*)malloc(sizeof(char) * got))
		return (NULL);
	i = 0;
	while (i < got)
	{
		ret[i] = tmp[i];
		i++;
	}
	return (ret);
}
