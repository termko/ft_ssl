#include "main.h"

int argv_parse(t_flags *flags, char *arg)
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

int parse_flags(t_flags *flags, t_flags *out, char **av)
{
    int not_flags = 2;

    flags->p = 0;
    flags->q = 0;
    flags->r = 0;
    flags->s = 0;
    while (argv_parse(flags, av[2]))
    {
        av++;
        not_flags++;
    }
    out->p = flags->p;
    out->q = flags->q;
    out->r = flags->r;
    out->s = flags->s;
    return (not_flags);
}