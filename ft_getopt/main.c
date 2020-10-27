#include "main.h"

void check_malloc(void *addr)
{
	if (!addr)
	{
		fprintf(stderr, "Error with malloc\n");
		exit(-1);
	}
}

t_opt *ft_init_opt(int ac, char **av, char *avail)
{
	t_opt *opt;

	check_malloc(opt = (t_opt*)malloc(sizeof(t_opt)));
	opt->ac = ac;
	opt->av = av;
	opt->avail = ft_strdup(avail);
	opt->pos = 0;
	opt->arg = NULL;
	return (opt);
}

char ft_getopt(t_opt *opt)
{
	
}

int main(int ac, char **av)
{
  char c;
  t_opt *opt;

  opt = ft_init_opt(ac, av, "");
  c = ft_getopt(opt);

  return (0);
}