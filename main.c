#include "main.h"

t_ssl *init_ssl(void)
{
    t_ssl	*ssl;
    char	*hash_names[HASH_COUNT] = {"md5", "sha256"};
    void	(*hash_init[HASH_COUNT])(int, char**) = {md5_init, sha256_init};
    int		i;

    check_malloc(ssl = (t_ssl*)malloc(sizeof(t_ssl)));
    i = 0;
    while (i < HASH_COUNT)
    {
        ssl->hash_names[i] = ft_strdup(hash_names[i]);
        ssl->hash_init[i] = hash_init[i];
        i++;
    }
    return (ssl);
}

int main(int ac, char **av)
{
    t_ssl *ssl;
    int i;
    
    if (ac < 2)
		ft_usage();
    ssl = init_ssl();
    i = 0;
    while (i < HASH_COUNT)
    {
        if (!ft_strcmp(av[1], ssl->hash_names[i]))
        {
            ssl->hash_init[i](ac, av);
            break ;
        }
        i++;
    }
    if (i == HASH_COUNT)
		wrong_command(ssl, av[1]);
    return (0);
}