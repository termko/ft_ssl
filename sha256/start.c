#include "../main.h"

void	sha256_start(t_sha256 *sha256, int ac, char **av)
{
	int i;
	int ret;

	ret = 0;
	i = sha256->not_flags;
	while (i < ac || sha256->not_flags == ac)
	{
		sha256_constants(sha256);
		ret = sha256_get_string(sha256, av[i]);
		if (!sha256->str)
		{
			i++;
			continue ;
		}
		sha256_set_length(sha256);
		sha256_prepare_message(sha256);
		sha256_main(sha256);
		sha256_output(sha256);
		sha256_free(&sha256);
		i += (sha256->not_flags == ac ? 0 : ret);
		sha256->not_flags = -1;
	}
}