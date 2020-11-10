#include "../main.h"

int		sha256_argv_parse(t_hashflags *flags, char *arg)
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

void	sha256_parse_flags(t_sha256 *sha256, char **av)
{
	int	not_flags = 2;

	sha256->flags.p = 0;
	sha256->flags.q = 0;
	sha256->flags.r = 0;
	sha256->flags.s = 0;
	while (sha256_argv_parse(&(sha256->flags), av[not_flags]))
		not_flags++;
	sha256->out.p = sha256->flags.p;
	sha256->out.q = sha256->flags.q;
	sha256->out.r = sha256->flags.r;
	sha256->out.s = sha256->flags.s;
	sha256->not_flags = not_flags;
}