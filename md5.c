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

void md5_output(t_ssl *ssl)
{
  t_md5 *md5;

  md5 = (t_md5*)ssl->sct;
  printf("%08x%08x%08x%08x",
            btol(md5->A), btol(md5->B), btol(md5->C), btol(md5->D));
}

void md5_main(t_ssl *ssl)
{
    uint32_t i;
    t_md5 *md5;

    md5 = (t_md5*)ssl->sct;
    while (md5->void_len / 64)
    {
        md5_reset_variables(md5);
        md5_cycle(md5);
        md5_update_variables(md5);
    }
}


void print_input(unsigned int *input, int len)
{
    int start;
    int end;
    char c;
    unsigned int maxPow = 1<<(sizeof(char)*8-1);
    
    int i=0,j;
    
    for(;i<len;++i){
        c = ((char*)input)[i];
        for(j=0;j<8;++j){
            printf("%u",c&maxPow ? 1 : 0);
            c <<= 1;
        }
        printf(" ");
        if ((i + 1) % 8 == 0 && i != 0)
            printf("\n");
    }
}

void md5_prepare_message(t_ssl *ssl)
{
  t_md5 *md5;
    int void_len_bits;
    int i;
    
    md5 = (t_md5*)ssl->sct;
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
        ((char*)(md5->input))[i] = ssl->str[i];
        i++;
    }
    ((char*)(md5->input))[i] = 0x80;
    ((long*)md5->input)[(md5->void_len / 8) - 1] = md5->bits_len;
}

void md5_set_length(t_ssl *ssl)
{
  t_md5 *md5;
  
  md5 = (t_md5*)ssl->sct;
  md5->len = ssl->len;
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

void md5_constants(t_ssl *ssl)
{
  t_md5 *md5;

  md5 = (t_md5*)ssl->sct;
  md5->A = 1732584193;
  md5->B = 4023233417;
  md5->C = 2562383102;
  md5->D = 271733878;
}

void md5_init_interfaces(t_ssl *ssl)
{
  ssl->constants = md5_constants;
  ssl->set_length = md5_set_length;
  ssl->prepare_message = md5_prepare_message;
  ssl->main = md5_main;
  ssl->output = md5_output;
  ssl->free_sct = md5_free_str;
}

void md5_init(t_ssl *ssl, int ac, char **av)
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
	ssl->sct = md5;
  ssl->hash = ft_strdup("MD5");
  md5_init_interfaces(ssl);
}