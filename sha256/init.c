#include "../main.h"

int		sha256_init(int ac, char **av)
{
    t_sha256 *sha256;
    
    if (check_malloc(sha256 = (t_sha256*)malloc(sizeof(t_sha256))))
		return (-1);
    sha256->r = get_r();
    sha256_parse_flags(sha256, av);
    return (sha256_start(sha256, ac, av));
}
