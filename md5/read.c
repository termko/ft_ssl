#include "../main.h"

void	md5_read_cycle(t_md5 *md5, char *tmp, int fd)
{
	int got;

	while ((got = read(fd, tmp, 1024)) > 0)
    {
		if (!md5->str)
			md5->str = ft_memdup(tmp, got);
		else
			md5->str = ft_realloc(&(md5->str), tmp, md5->len, got);
		ft_bzero(tmp, 1024);
        md5->len += got;
    }
}

void	md5_read_file(t_md5 *md5, char *file)
{
    char tmp[1024];
    int fd;

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
    md5->str = NULL;
    md5->len = 0;
    ft_bzero(tmp, sizeof(char) * 1024);
    md5_read_cycle(md5, tmp, fd);
    if (!file && !md5->str)
        md5->str = ft_strdup("");
    if (file)
        close(fd);
}

int		md5_get_string(t_md5 *md5, char *str)
{
	if (md5->flags.p)
	{
		md5->flags.p = 0;
		md5_read_file(md5, NULL);
		return (0);
	}
	if (!str)
	{
		md5_read_file(md5, NULL);
		md5->file = ft_strdup("stdin");
		return (0);
	}
	if (md5->flags.s)
	{
		md5->flags.s = 0;
		md5->str = ft_strdup(str);
		md5->len = ft_strlen(str);
		return (1);
	}
	md5_read_file(md5, str);
	md5->file = ft_strdup(str);
	return (1);
}