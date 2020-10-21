#include "main.h"

void md5_reset_variables(t_md5 *md5)
{
    md5->aa = md5->A;
    md5->bb = md5->B;
    md5->cc = md5->C;
    md5->dd = md5->D;
    md5->i = 0;
}

void md5_update_variables(t_md5 *md5)
{
    md5->A += md5->aa;
    md5->B += md5->bb;
    md5->C += md5->cc;
    md5->D += md5->dd;
    md5->void_len -= 64;
    md5->input += 64;
}

void md5_cycle(t_md5 *md5)
{
    while (md5->i < 64)
    {
        md5->rounds[md5->i / 16](md5);
        md5->tmp = md5->D;
        md5->D = md5->C;
        md5->C = md5->B;
        md5->B += ft_leftrotate(md5->A + md5->f + md5->k[md5->i] +
                ((uint32_t*)md5->input)[md5->g], md5->s[md5->i]);
        md5->A = md5->tmp;
        md5->i++;
    }
}

void md5_hash_output(t_md5 *md5)
{
  printf("%08x%08x%08x%08x",
            btol(md5->A), btol(md5->B), btol(md5->C), btol(md5->D));
}

void md5_output(t_md5 *md5)
{
    if (md5->out.p)
    {
        printf("%s", md5->str);
        md5_hash_output(md5);
        printf("\n");
        md5->out.p = 0;
        return ;
    }
    if (!md5->out.q)
    {
        if (md5->out.r)
        {
            md5_hash_output(md5);
            if (md5->out.s)
            {
                printf(" \"%s\"", md5->str);
                md5->out.s = 0;
            }
            else
                printf(" %s", md5->file);
        }   
        else
        {
            printf("MD5(");
            if (md5->out.s)
            {
                printf("\"%s\")= ", md5->str);
                md5->out.s = 0;
            }
            else
                printf("%s)= ", md5->file);
            md5_hash_output(md5);
        }
    }
    else
        md5_hash_output(md5);
    printf("\n");
}

void md5_main(t_md5 *md5)
{
    while (md5->void_len / 64)
    {
        md5_reset_variables(md5);
        md5_cycle(md5);
        md5_update_variables(md5);
    }
}

void md5_prepare_message(t_md5 *md5)
{
    uint64_t void_len_bits;
    uint32_t i;
    
    void_len_bits = md5->append_len + md5->bits_len;
    md5->void_len = (void_len_bits % 8 ?
            (void_len_bits / 8) + 1 : void_len_bits / 8);
    md5->input = malloc(md5->void_len);
    if (!(md5->input))
    {
        printf("Malloc Error\n");
        exit(-1);
    }
    ft_bzero(md5->input, md5->void_len);
    i = 0;
    while (i < md5->len)
    {
        ((char*)(md5->input))[i] = md5->str[i];
        i++;
    }
    ((char*)(md5->input))[i] = 0x80;
    ((long*)md5->input)[(md5->void_len / 8) - 1] = md5->bits_len;
}

void md5_set_length(t_md5 *md5)
{
    md5->bits_len = md5->len * 8;
    md5->append_len = 512 - (md5->bits_len % 512);
    md5->zeroes_len = 512 - md5->append_len - 65;
}

void md5_free_str(t_ssl **ssl)
{
    if ((*ssl)->str)
        free((*ssl)->str);
    (*ssl)->str = NULL;
    if ((*ssl)->file)
        free((*ssl)->file);
    (*ssl)->file = NULL;
}

void md5_constants(t_md5 *md5)
{
  md5->A = 1732584193;
  md5->B = 4023233417;
  md5->C = 2562383102;
  md5->D = 271733878;
}

void md5_read_file(t_md5 *md5, char *file)
{
    char tmp[1024];
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
    md5->str = NULL;
    md5->len = 0;
    ft_bzero(tmp, sizeof(char) * 1024);
    i = 1;
    while ((got = read(fd, tmp, (file ? 1024 : 1))) > 0)
    {
        if (!md5->str)
            md5->str = ft_memdup(tmp, got);
        else
            md5->str = ft_realloc(&(md5->str), tmp, md5->len, got);
        ft_bzero(tmp, 1024);
        md5->len += got;
        i++;
    }
    if (!file && !md5->str)
        md5->str = ft_strdup("");
    if (file)
        close(fd);
}

int md5_get_string(t_md5 *md5, char *str)
{
    if (md5->flags.p)
    {
        md5->flags.p = 0;
        md5_read_file(md5, NULL);
        return (0);
    }
    if (!str)
    {
        md5_read_file(md5, NULL);
        md5->file = ft_strdup("stdin");
        return (0);
    }
    if (md5->flags.s)
    {
        md5->flags.s = 0;
        md5->str = ft_strdup(str);
        md5->len = ft_strlen(str);
        return (1);
    }
    md5_read_file(md5, str);
    md5->file = ft_strdup(str);
    return (1);
}

void md5_free(t_md5 **md5)
{
  if ((*md5)->str)
    free((*md5)->str);
  (*md5)->str = NULL;
  if ((*md5)->file)
    free((*md5)->file);
  (*md5)->file = NULL;
}

void md5_start(t_md5 *md5, int ac, char **av)
{
    int i;
    int ret;
    
    ret = 0;
    i = md5->not_flags;
    while (i < ac || md5->not_flags == ac)
    {
        md5_constants(md5);
        ret = md5_get_string(md5, av[i]);
        if (!md5->str)
        {
            i++;
            continue ;
        }
        md5_set_length(md5);
        md5_prepare_message(md5);
        md5_main(md5);
        md5_output(md5);
        md5_free(&md5);
        i += (md5->not_flags == ac ? 0 : ret);
        md5->not_flags = -1;
    }
}

int md5_argv_parse(t_flags *flags, char *arg)
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

void md5_parse_flags(t_md5 *md5, char **av)
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

void md5_init(int ac, char **av)
{
    t_md5 *md5;
    void (*rounds[4])(t_md5*) = {ft_f, ft_g, ft_h, ft_i};
    int i;
    
    md5 = (t_md5*)malloc(sizeof(t_md5));
    if (!md5)
    {
        printf("Error with malloc\n");
        exit(1);
    }
    md5->k = get_k();
    md5->s = get_s();
    i = 0;
    while (i < 4)
    {
        md5->rounds[i] = rounds[i];
        i++;
    }
  md5_parse_flags(md5, av);
  md5_start(md5, ac, av);
}