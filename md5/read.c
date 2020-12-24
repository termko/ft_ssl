#include "../main.h"

int	md5_read_cycle(t_md5 *md5, char *tmp, int fd)
{
	int got;

	while ((got = read(fd, tmp, 1024)) > 0)
	{
		if (!md5->str)
		{
			if (check_malloc(md5->str = ft_memdup(tmp, got)))
				return (-1);
		}
		else
			if (check_malloc(md5->str = ft_realloc(&(md5->str), tmp, md5->len, got)))
				return (-1);
		ft_bzero(tmp, 1024);
		md5->len += got;
	}
	return (0);
}

int	md5_read_file(t_md5 *md5, char *file)
{
    char tmp[1024];
    int fd;

    if (file)
    {
        fd = open(file, O_RDONLY);
        if (fd < 0)
        {
//            printf("OOOOOO WRONG FILE BABE '%s'\n", file); REMAKE ME
			ft_putstr("PLACEHOLDER\n");
            return 0;
        }
    }
    else
        fd = STDIN_FILENO;
    md5->str = NULL;
    md5->len = 0;
    ft_bzero(tmp, sizeof(char) * 1024);
	if (md5_read_cycle(md5, tmp, fd) == -1)
		return (-1);
	if (!file && !md5->str)
		if (check_malloc(md5->str = ft_strdup("")))
			return (-1);
	if (file)
		close(fd);
	return (0);
}

int		md5_get_string(t_md5 *md5, char *str)
{
	if (md5->flags.p)
	{
		md5->flags.p = 0;
		return (md5_read_file(md5, NULL));
	}
	if (!str)
	{
		if (check_malloc(md5->file = ft_strdup("stdin")))
			return (-1);
		return (md5_read_file(md5, NULL));
	}
	if (md5->flags.s)
	{
		md5->flags.s = 0;
		md5->len = ft_strlen(str);
		if (check_malloc(md5->str = ft_strdup(str)))
			return (-1);
		return (1);
	}
	if (md5_read_file(md5, str))
		return (-1);
	if (check_malloc(md5->file = ft_strdup(str)))
		return (-1);
	return (1);
}
