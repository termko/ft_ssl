#include "../main.h"

void	sha256_init(int ac, char **av)
{
    t_sha256 *sha256;
    
    sha256 = (t_sha256*)malloc(sizeof(t_sha256));
    if (!sha256)
    {
        ft_putstr("Error with Malloc\n");
        exit(1);
    }
    sha256->r = get_r();
    sha256_parse_flags(sha256, av);
    sha256_start(sha256, ac, av);
}
