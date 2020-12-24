#include "../main.h"

int		sha256_read_cycle(t_sha256 *sha256, char *tmp, int fd)
{
	int	got;

	while ((got = read(fd, tmp, 1024)) > 0)
	{
		if (!sha256->str)
		{
			if (check_malloc(sha256->str = ft_memdup(tmp, got)))
				return (-1);
		}
		else
			if (check_malloc(sha256->str = ft_realloc(&(sha256->str), tmp, sha256->len, got)))
				return (-1);
		ft_bzero(tmp, 1024);
		sha256->len += got;
	}
	return (0);
}

int		sha256_read_file(t_sha256 *sha256, char *file)
{
	char	tmp[1024];
	int		fd;

	if (file)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			// printf("OOOOOO WRONG FILE BABE '%s'\n", file); REMAKE ME!
			ft_putstr("PLACEHOLDER\n");
			return (0);
		}
	}
	else
		fd = STDIN_FILENO;
	sha256->str = NULL;
	sha256->len = 0;
	ft_bzero(tmp, sizeof(char) * 1024);
	if (sha256_read_cycle(sha256, tmp, fd) == -1)
		return (-1);
	if (!file && !sha256->str)
		if (check_malloc(sha256->str = ft_strdup("")))
			return (-1);
	if (file)
		close(fd);
	return (0);
}

int		sha256_get_string(t_sha256 *sha256, char *str)
{
	if (sha256->flags.p)
	{
		sha256->flags.p = 0;
		return (sha256_read_file(sha256, NULL));
	}
	if (!str)
	{
		if (check_malloc(sha256->file = ft_strdup("stdin")))
			return (-1);
		return (sha256_read_file(sha256, NULL));
	}
	if (sha256->flags.s)
	{
		sha256->flags.s = 0;
		sha256->len = ft_strlen(str);
		if (check_malloc(sha256->str = ft_strdup(str)))
			return (-1);
		return (1);
	}
	if (sha256_read_file(sha256, str))
		return (-1);
	if (check_malloc(sha256->file = ft_strdup(str)))
		return (-1);
	return (1);
}
