#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#define HASH_COUNT 3

typedef struct  s_hashflags
{
    char p;
    char q;
    char r;
    char s;
}               t_hashflags;

typedef struct  s_baseflags
{
    char d;
    char e;
    char i;
    char o;
}               t_baseflags;

typedef struct  s_ssl
{
    char *names[HASH_COUNT];
    void (*init[HASH_COUNT])(int, char**);
    void (*constants)(struct s_ssl*);
    void (*set_length)(struct s_ssl*);
    void (*prepare_message)(struct s_ssl*);
    void (*main)(struct s_ssl*);
    void (*output)(struct s_ssl*);
    void (*free_sct)(struct s_ssl**);

    char *hash;
    void *sct;
    char *str;
    char *file;
    uint32_t len;
}               t_ssl;

typedef struct  s_md5
{
    char *str;
    void *input;
    uint32_t len;
    uint64_t bits_len;
    uint64_t append_len;
    uint64_t needed_len;
    uint64_t zeroes_len;
    uint32_t void_len;
    uint32_t A;
    uint32_t B;
    uint32_t C;
    uint32_t D;
    uint32_t aa;
    uint32_t bb;
    uint32_t cc;
    uint32_t dd;
    uint32_t g;
    uint32_t f;
    uint32_t tmp;
    uint32_t i;
    uint32_t *k;
    uint32_t *s;
    char *file;
    t_hashflags flags;
    t_hashflags out;
    int not_flags;
    void (*rounds[4])(struct s_md5*);
}               t_md5;

typedef struct  s_sha256
{
    uint32_t h0;
    uint32_t h1;
    uint32_t h2;
    uint32_t h3;
    uint32_t h4;
    uint32_t h5;
    uint32_t h6;
    uint32_t h7;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint32_t s0;
    uint32_t s1;
    uint32_t ch;
    uint32_t tmp1;
    uint32_t tmp2;
    uint32_t maj;
    uint32_t *w;
    uint32_t *r;
    uint64_t len;
    uint64_t bits_len;
    uint64_t append_len;
    uint32_t void_len;
    uint32_t needed_len;
    uint32_t zeroes_len;
    t_hashflags flags;
    t_hashflags out;
    int not_flags;
    void *input;
    char *str;
    char *file;
}               t_sha256;

typedef struct  s_b64
{
    char *outfile;
    char *infile;
    char *str;
    char *result;
    t_baseflags flags;
}               t_b64;

void ft_f(t_md5 *md5);
void ft_g(t_md5 *md5);
void ft_h(t_md5 *md5);
void ft_i(t_md5 *md5);
uint32_t *get_s(void);
uint32_t *get_k(void);
long ft_strlen(char *str);
char *ft_strdup(char *str);
char *ft_realloc(char **str, char *tmp, int total, int got);
void ft_bzero(void *ptr, int len);
char *ft_memdup(char *tmp, int got);
uint32_t btol(uint32_t num);
void ft_md5(t_ssl *ssl, int ac, char **av);
int parse_flags(t_ssl *ssl, char **av);
uint32_t ft_leftrotate(uint32_t what, uint32_t to);
uint32_t ft_rightrotate(uint32_t what, uint32_t to);
void ft_sha256(t_ssl *ssl, int ac, char **av);
int ft_strcmp(char *s1, char *s2);
void md5_init(int ac, char **av);
void sha256_init(int ac, char **av);
void start(t_ssl *ssl, int ac, char **av);
void base64_init(int ac, char **av);