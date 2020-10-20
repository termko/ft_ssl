#include "main.h"

void set_length(void *input, uint32_t len, uint64_t len_bits)
{
    void *tmp;
    int i;
    
    i = 0;
    tmp = &(len_bits);
    while (i < 8)
    {
        ((char*)input)[len - 8 + i] =
                ((char*)tmp)[7 - i];
        i++;
    }
}

uint32_t *get_r(void)
{
    static uint32_t r[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    
    return (r);
}

uint32_t sha256_get_uint32(t_sha256 *sha256, int i)
{
    int j;
    unsigned char num[4];

    j = 0;
    while (j < 4)
    {
        num[j] = ((unsigned char*)(sha256->input))[j + i * 4];
        j++;
    }
    return ((uint32_t)(num[0] << 24 | num[1] << 16 | num[2] << 8 | num[3]));
}

uint32_t *initialize_w(t_sha256 *sha256)
{
    static uint32_t w[64];
    int i;
    
    i = 0;
    while (i < 16)
    {
        w[i] = sha256_get_uint32(sha256, i);
        i++;
    }
    while (i < 64)
    {
        sha256->s0 = (ft_rightrotate(w[i - 15], 7) ^
            ft_rightrotate(w[i - 15], 18) ^ (w[i - 15] >> 3));
        sha256->s1 = (ft_rightrotate(w[i - 2], 17) ^
            ft_rightrotate(w[i - 2], 19) ^ (w[i - 2] >> 10));
        w[i] = w[i - 16] + sha256->s0 + w[i - 7] + sha256->s1;
        i++;
    }
    return (w);
}

void sha256_reset_variables(t_sha256 *sha256)
{
        sha256->a = sha256->h0;
        sha256->b = sha256->h1;
        sha256->c = sha256->h2;
        sha256->d = sha256->h3;
        sha256->e = sha256->h4;
        sha256->f = sha256->h5;
        sha256->g = sha256->h6;
        sha256->h = sha256->h7;
}

void sha256_cycle(t_sha256 *s)
{
    int i;

    i = 0;
    while (i < 64)
    {
        s->s1 = ft_rightrotate(s->e, 6) ^ ft_rightrotate(s->e, 11) ^ ft_rightrotate(s->e, 25);
        s->ch = (s->e & s->f) ^ (~(s->e) & s->g);
        s->tmp1 = s->h + s->s1 + s->ch + s->r[i] + s->w[i];
        s->s0 = ft_rightrotate(s->a, 2) ^ ft_rightrotate(s->a, 13) ^ ft_rightrotate(s->a, 22);
        s->maj = (s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c);
        s->tmp2 = s->s0 + s->maj;
        s->h = s->g;
        s->g = s->f;
        s->f = s->e;
        s->e = s->d + s->tmp1;
        s->d = s->c;
        s->c = s->b;
        s->b = s->a;
        s->a = s->tmp1 + s->tmp2;
        i++;
    }
}

void sha256_update_variables(t_sha256 *sha256)
{
    sha256->h0 += sha256->a;
    sha256->h1 += sha256->b;
    sha256->h2 += sha256->c;
    sha256->h3 += sha256->d;
    sha256->h4 += sha256->e;
    sha256->h5 += sha256->f;
    sha256->h6 += sha256->g;
    sha256->h7 += sha256->h;
}

void sha256_start(t_sha256 *sha256, int ac, char **av)
{
    int i;

    while (sha256->void_len / 64)
    {
        sha256->w = initialize_w(sha256);
        sha256_reset_variables(sha256);
        sha256_cycle(sha256);
        sha256_update_variables(sha256);
        sha256->void_len -= 64;
        sha256->input += 64;
    }
    printf("%08x%08x%08x%08x%08x%08x%08x%08x",
            sha256->h0, sha256->h1, sha256->h2, sha256->h3,
            sha256->h4, sha256->h5, sha256->h6, sha256->h7);
}

void sha256_init_len(t_sha256 *sha256, int ac, char **av)
{
    sha256->str = av[2];
    sha256->len = ft_strlen(sha256->str);
    sha256->bits_len = sha256->len * 8;
    sha256->append_len = 512 - (sha256->bits_len % 512);
    sha256->zeroes_len = 512 - sha256->append_len - 65;
}

void sha256_prepare_message(t_sha256 *sha256)
{
    long len_bits;
    uint32_t void_len_bits;
    int i;
    
    len_bits = sha256->len * 8;
    void_len_bits = sha256->append_len + len_bits;
    sha256->void_len = (void_len_bits % 8 ?
            (void_len_bits / 8) + 1 : void_len_bits / 8);
    sha256->input = malloc(sha256->void_len);
    ft_bzero(sha256->input, sha256->void_len);
    if (!sha256->input)
    {
        printf("Malloc Error\n");
        exit(-1);
    }
    i = 0;
    while (i < sha256->len)
    {
        ((char*)(sha256->input))[i] = sha256->str[i];
        i++;
    }
    ((char*)sha256->input)[i] = 0x80;
    set_length(sha256->input, sha256->void_len, len_bits);
}

t_sha256 *sha256_init(int ac, char **av)
{
    t_sha256 *sha256;
    
    sha256 = (t_sha256*)malloc(sizeof(t_sha256));
    if (!sha256)
    {
        printf("Error with Malloc\n");
        exit(1);
    }
    sha256->h0 = 0x6a09e667;
    sha256->h1 = 0xbb67ae85;
    sha256->h2 = 0x3c6ef372;
    sha256->h3 = 0xa54ff53a;
    sha256->h4 = 0x510e527f;
    sha256->h5 = 0x9b05688c;
    sha256->h6 = 0x1f83d9ab;
    sha256->h7 = 0x5be0cd19;
    sha256->r = get_r();
    sha256->not_flags = parse_flags(&(sha256->flags), &(sha256->out), av);
    sha256_init_len(sha256, ac, av);
    sha256_prepare_message(sha256);
    return (sha256);
}

void ft_sha256(int ac, char **av)
{
    t_sha256 *sha256;
    
    sha256 = sha256_init(ac, av);
    sha256_start(sha256, ac, av);
}