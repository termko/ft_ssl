#include "../main.h"

void	sha256_read_cycle(t_sha256 *sha256, char *tmp, int fd)
{
	int	got;

	while ((got = read(fd, tmp, 1024)) > 0)
	{
		if (!sha256->str)
			sha256->str = ft_memdup(tmp, got);
		else
			sha256->str = ft_realloc(&(sha256->str), tmp, sha256->len, got);
		ft_bzero(tmp, 1024);
		sha256->len += got;
	}
}

void	sha256_read_file(t_sha256 *sha256, char *file)
{
	char	tmp[1024];
	int		fd;

	if (file)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			printf("OOOOOO WRONG FILE BABE '%s'\n", file);
			return ;
		}
	}
	else
		fd = STDIN_FILENO;
	sha256->str = NULL;
	sha256->len = 0;
	ft_bzero(tmp, sizeof(char) * 1024);
	sha256_read_cycle(sha256, tmp, fd);
	if (!file && !sha256->str)
		sha256->str = ft_strdup("");
	if (file)
		close(fd);
}

int		sha256_get_string(t_sha256 *sha256, char *str)
{
	if (sha256->flags.p)
	{
		sha256->flags.p = 0;
		sha256_read_file(sha256, NULL);
		return (0);
	}
	if (!str)
	{
		sha256_read_file(sha256, NULL);
		sha256->file = ft_strdup("stdin");
		return (0);
	}
	if (sha256->flags.s)
	{
		sha256->flags.s = 0;
		sha256->str = ft_strdup(str);
		sha256->len = ft_strlen(str);
		return (1);
	}
	sha256_read_file(sha256, str);
	sha256->file = ft_strdup(str);
	return (1);
}