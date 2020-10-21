#include "main.h"

int md5_argv_parse(t_baseflags *flags, char *arg)
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
        return (1);
    else
        return (0);
    return (1);
}

void b64_parse_flags(t_b64 *b64, char **av)
{
    int not_flags = 2;

    // b64->flags.p = 0;
    // b64->flags.q = 0;
    // b64->flags.r = 0;
    // b64->flags.s = 0;
    while (md5_argv_parse(&(b64->flags), av[2]))
    {
        av++;
        not_flags++;
    }
    // b64->out.p = b64->flags.p;
    // b64->out.q = b64->flags.q;
    // b64->out.r = b64->flags.r;
    // b64->out.s = b64->flags.s;
    // b64->not_flags = not_flags;
}

void base64_init(int ac, char **av)
{

}