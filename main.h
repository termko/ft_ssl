#ifndef MAIN_H
# define MAIN_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# define HASH_COUNT 2

typedef struct	s_hashflags
{
	char	p;
	char	q;
	char	r;
	char	s;
}				t_hashflags;

typedef struct	s_ssl
{
    char	*hash_names[HASH_COUNT];
    void	(*hash_init[HASH_COUNT])(int, char**);
}				t_ssl;

typedef struct	s_sha256
{
    uint32_t	h0;
    uint32_t	h1;
    uint32_t	h2;
    uint32_t	h3;
    uint32_t	h4;
    uint32_t	h5;
    uint32_t	h6;
    uint32_t	h7;
    uint32_t	a;
    uint32_t	b;
    uint32_t	c;
    uint32_t	d;
    uint32_t	e;
    uint32_t	f;
    uint32_t	g;
    uint32_t	h;
    uint32_t	s0;
    uint32_t	s1;
    uint32_t	ch;
    uint32_t	tmp1;
    uint32_t	tmp2;
    uint32_t	maj;
    uint32_t	*w;
    uint32_t	*r;
    uint64_t	len;
    uint64_t	bits_len;
    uint64_t	append_len;
    uint32_t	void_len;
    uint32_t	needed_len;
    uint32_t	zeroes_len;
    t_hashflags	flags;
    t_hashflags	out;
    int			not_flags;
    void		*input;
    char		*str;
    char		*file;
}				t_sha256;

typedef struct	s_md5
{
    char		*str;
    void		*input;
    uint32_t	len;
    uint64_t	bits_len;
    uint64_t	append_len;
    uint64_t	needed_len;
    uint64_t	zeroes_len;
    uint32_t	void_len;
    uint32_t	A;
    uint32_t	B;
    uint32_t	C;
    uint32_t	D;
    uint32_t	aa;
    uint32_t	bb;
    uint32_t	cc;
    uint32_t	dd;
    uint32_t	g;
    uint32_t	f;
    uint32_t	tmp;
    uint32_t	i;
    uint32_t	*k;
    uint32_t	*s;
    char		*file;
    t_hashflags	flags;
    t_hashflags	out;
    int			not_flags;
    void		(*rounds[4])(struct s_md5*);
}               t_md5;

uint32_t	*get_s(void);
uint32_t	*get_k(void);
long		ft_strlen(char *str);
char		*ft_strdup(char *str);
void		ft_putstr(char *str);
char		*ft_realloc(char **str, char *tmp, int total, int got);
void		ft_bzero(void *ptr, int len);
char		*ft_memdup(char *tmp, int got);
uint32_t	btol(uint32_t num);
uint32_t	ft_leftrotate(uint32_t what, uint32_t to);
uint32_t	ft_rightrotate(uint32_t what, uint32_t to);
void		ft_sha256(t_ssl *ssl, int ac, char **av);
int			ft_strcmp(char *s1, char *s2);
void		sha256_init(int ac, char **av);
char		*ft_strnew(int size);
void		check_malloc(void *addr);
void		ft_usage(void);
void		wrong_command(t_ssl *ssl, char *str);
void		ft_f(t_md5 *md5);
void		ft_g(t_md5 *md5);
void		ft_h(t_md5 *md5);
void		ft_i(t_md5 *md5);
void		md5_parse_flags(t_md5 *md5, char **av);
void		md5_main(t_md5 *md5);
void		md5_start(t_md5 *md5, int ac, char **av);
void		md5_init(int ac, char **av);
void		md5_constants(t_md5 *md5);
int			md5_get_string(t_md5 *md5, char *str);
void		md5_set_length(t_md5 *md5);
void		md5_prepare_message(t_md5 *md5);
void		md5_output(t_md5 *md5);
void		md5_free(t_md5 **md5);
void		sha256_constants(t_sha256 *sha256);
int			sha256_get_string(t_sha256 *sha256, char *str);
void		sha256_set_length(t_sha256 *sha256);
void		sha256_prepare_message(t_sha256 *sha256);
void		sha256_main(t_sha256 *sha256);
void		sha256_output(t_sha256 *sha256);
void		sha256_free(t_sha256 **sha256);
uint32_t	*initialize_w(t_sha256 *sha256);
uint32_t	*get_r(void);
void		sha256_parse_flags(t_sha256 *sha256, char **av);
void		sha256_start(t_sha256 *sha256, int ac, char **av);
#endif
