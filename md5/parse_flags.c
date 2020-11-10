#include "../main.h"

int		md5_argv_parse(t_hashflags *flags, char *arg)
{
	uint32_t len;

	if (!arg)
		return (0);
	len = ft_strlen(arg);
	if (len != 2)
		return (0);
	if (arg[0] != '-')
		return (0);
	if (arg[1] != 'p' && arg[1] != 'q' && arg[1] != 'r' && arg[1] != 's')
		return (0);
	if (arg[1] == 'p')
		flags->p = 1;
	else if (arg[1] == 'q')
		flags->q = 1;
	else if (arg[1] == 'r')
		flags->r = 1;
	else if (arg[1] == 's')
		flags->s = 1;
	else
		return (0);
	return (1);
}

void	md5_parse_flags(t_md5 *md5, char **av)
{
	int not_flags = 2;

	md5->flags.p = 0;
	md5->flags.q = 0;
	md5->flags.r = 0;
	md5->flags.s = 0;
	while (md5_argv_parse(&(md5->flags), av[2]))
	{
		av++;
		not_flags++;
	}
	md5->out.p = md5->flags.p;
	md5->out.q = md5->flags.q;
	md5->out.r = md5->flags.r;
	md5->out.s = md5->flags.s;
	md5->not_flags = not_flags;
}