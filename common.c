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

int parse_flags(t_ssl *ssl, char **av)
{
    int not_flags = 2;

    ssl->flags.p = 0;
    ssl->flags.q = 0;
    ssl->flags.r = 0;
    ssl->flags.s = 0;
    while (argv_parse(&(ssl->flags), av[2]))
    {
        av++;
        not_flags++;
    }
    ssl->out.p = ssl->flags.p;
    ssl->out.q = ssl->flags.q;
    ssl->out.r = ssl->flags.r;
    ssl->out.s = ssl->flags.s;
    ssl->not_flags = not_flags;
    return (not_flags);
}

void read_file(t_ssl *ssl, char *file)
{
    char tmp[1025];
    int i;
    int fd;
    int got;
    
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
    ssl->str = NULL;
    ssl->len = 0;
    ft_bzero(tmp, sizeof(char) * 1024);
    i = 1;
    while ((got = read(fd, tmp, (file ? 1024 : 1))) > 0)
    {
        if (!ssl->str)
            ssl->str = ft_memdup(tmp, got);
        else
            ssl->str = ft_realloc(&(ssl->str), tmp, ssl->len, got);
        ft_bzero(tmp, 1024);
        ssl->len += got;
        i++;
    }
    if (!file && !ssl->str)
        ssl->str = ft_strdup("");
    if (file)
        close(fd);
}

int get_string(t_ssl *ssl, char *str)
{
    if (ssl->flags.p)
    {
        ssl->flags.p = 0;
        read_file(ssl, NULL);
        return (0);
    }
    if (!str)
    {
        read_file(ssl, NULL);
        ssl->file = ft_strdup("stdin");
        return (0);
    }
    if (ssl->flags.s)
    {
        ssl->flags.s = 0;
        ssl->str = ft_strdup(str);
        ssl->len = ft_strlen(str);
        return (1);
    }
    read_file(ssl, str);
    ssl->file = ft_strdup(str);
    return (1);
}

void output(t_ssl *ssl)
{
    if (ssl->out.p)
    {
        printf("%s", ssl->str);
        ssl->output(ssl);
        printf("\n");
        ssl->out.p = 0;
        return ;
    }
    if (!ssl->out.q)
    {
        if (ssl->out.r)
        {
            ssl->output(ssl);
            if (ssl->out.s)
            {
                printf("\"%s\"\n", ssl->str);
                ssl->out.s = 0;
            }
            else
                printf("%s\n", ssl->file);
        }   
        else
        {
            printf("%s (", ssl->hash);
            if (ssl->out.s)
            {
                printf("\"%s\") = ", ssl->str);
                ssl->out.s = 0;
            }
            else
                printf("%s) = ", ssl->file);
            ssl->output(ssl);
        }
    }
    else
        ssl->output(ssl);
    printf("\n");
}

void start(t_ssl *ssl, int ac, char **av)
{
    int i;
    int ret;
    
    ret = 0;
    i = ssl->not_flags;
    // CHECK ORIGINAL ON 'openssl md5 -s', for example
    while (i < ac || ssl->not_flags == ac)
    {
        ssl->constants(ssl);
        ret = get_string(ssl, av[i]);
        if (!ssl->str)
        {
            i++;
            continue ;
        }
        ssl->set_length(ssl);
        ssl->prepare_message(ssl);
        ssl->main(ssl);
        output(ssl);
        ssl->free_sct(&ssl);
        i += (ssl->not_flags == ac ? 0 : ret);
        ssl->not_flags = -1;
    }
}