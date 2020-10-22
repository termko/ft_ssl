#include "main.h"

char *malloc_char(int size)
{
    char *ret;
    int i;
    
    ret = (char*)malloc(sizeof(char) * size);
    if (!ret)
    {
        printf("Malloc error\n");
        exit(-1);
    }
    i = 0;
    while (i < size)
    {
        ret[i] = '\0';
        i++;
    }
    return ret;
}

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

char *ft_strdup(char *str)
{
    char *ret;
    int len;
    int i;
    
    if (!str)
        return (NULL);
    len = 0;
    while (str[len])
        len++;
    ret = (char*)malloc(sizeof(char) * (len + 1));
    if (ret)
    {
        i = 0;
        while (i < len)
        {
            ret[i] = str[i];
            i++;
        }
    }
    ret[i] = '\0';
    return (ret);
}

void ft_f(t_md5 *md5)
{
    md5->f = ((md5->B & md5->C) | (~(md5->B) & md5->D));
    md5->g = md5->i;
}


void ft_g(t_md5 *md5)
{
    md5->f = ((md5->B & md5->D) | (md5->C & ~(md5->D)));
    md5->g = (5 * md5->i + 1) % 16;;
}


void ft_h(t_md5 *md5)
{
    md5->f = (md5->B ^ md5->C ^ md5->D);
    md5->g = (3 * md5->i + 5) % 16;
}


void ft_i(t_md5 *md5)
{
    md5->f = (md5->C ^ (md5->B | ~(md5->D)));
    md5->g = (7 * md5->i) % 16;
}

uint32_t btol(uint32_t num)
{
    return (((num>>24)&0xff) |
                    ((num<<8)&0xff0000) |
                    ((num>>8)&0xff00) |
                    ((num<<24)&0xff000000));
}

void ft_bzero(void *ptr, int len)
{
    int i;
    
    i = 0;
    while (i < len)
    {
        ((char*)ptr)[i] = '\0';
        i++;
    }
}

char *ft_memdup(char *tmp, int got)
{
  char *ret;
  int i;

  ret = (char*)malloc(sizeof(char) * got);
  if (!ret)
  {
    printf("Error with malloc\n");
    exit(-1);
  }
  i = 0;
  while (i < got)
  {
    ret[i] = tmp[i];
    i++;
  }
  return (ret);
}

char *ft_realloc(char **str, char *tmp, int total, int got)
{
    char *ret;
    int i;
    int j;
    
    i = 0;
    ret = malloc_char(total + got);
    while (i < total)
    {
        ret[i] = (*str)[i];
        i++;
    }
    j = 0;
    while (j < got)
    {
        ret[i + j] = tmp[j];
        j++;
    }
    free(*str);
    return (ret);
}

long ft_strlen(char *str)
{
    int len;
    
    len = 0;
    while (str[len])
        len++;
    return len;
}

uint32_t *get_s(void)
{
    static uint32_t s[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    
    return (s);
}

uint32_t *get_k(void)
{
    static uint32_t k[64] = {
        3614090360, 3905402710, 606105819, 3250441966,
        4118548399, 1200080426, 2821735955, 4249261313,
        1770035416, 2336552879, 4294925233, 2304563134,
        1804603682, 4254626195, 2792965006, 1236535329,
        4129170786, 3225465664, 643717713,3921069994,
        3593408605, 38016083, 3634488961, 3889429448,
        568446438, 3275163606, 4107603335, 1163531501,
        2850285829, 4243563512, 1735328473, 2368359562,
        4294588738, 2272392833, 1839030562, 4259657740,
        2763975236, 1272893353, 4139469664, 3200236656,
        681279174, 3936430074, 3572445317, 76029189,
        3654602809, 3873151461, 530742520, 3299628645,
        4096336452, 1126891415, 2878612391, 4237533241,
        1700485571, 2399980690, 4293915773, 2240044497,
        1873313359, 4264355552, 2734768916, 1309151649,
        4149444226, 3174756917, 718787259, 3951481745
    };

    return (k);
}

void print_input(unsigned int *input, int len);

uint32_t ft_leftrotate(uint32_t what, uint32_t to)
{
    return ((uint32_t)((what << to) | (what >> (32 - to))));
}

uint32_t ft_rightrotate(uint32_t what, uint32_t to)
{
    return ((uint32_t)((what >> to) | (what << (32 - to))));
}

t_ssl *init_ssl(void)
{
    t_ssl *ssl;
    char *hash_names[HASH_COUNT] = {"md5", "sha256"};
    char *cipher_names[CIPHER_COUNT] = {"base64"};
    void (*hash_init[HASH_COUNT])(int, char**) = {md5_init, sha256_init};
    void (*cipher_init[CIPHER_COUNT])(int, char**) = {base64_init};
    int i;
    
    ssl = (t_ssl*)malloc(sizeof(t_ssl));
    if (!ssl)
    {
        printf("Error with malloc\n");
        exit(1);
    }
    i = 0;
    while (i < HASH_COUNT)
    {
        ssl->hash_names[i] = ft_strdup(hash_names[i]);
        ssl->hash_init[i] = hash_init[i];
        i++;
    }
    i = 0;
    while (i < CIPHER_COUNT)
    {
      ssl->cipher_names[i] = ft_strdup(cipher_names[i]);
      ssl->cipher_init[i] = cipher_init[i];
      i++;
    }
    return (ssl);
}

int main(int ac, char **av)
{
    t_ssl *ssl;
    int i;
    
    if (ac < 2)
    {
        printf("usage: ft_ssl command [command opts] [command args]\n");
        exit(1);
    }
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
    if (i == HASH_COUNT) // OH GOD ITS UGLY MAKE A FLAG OR SMTH FFS
    {
      i = 0;
      while (i < CIPHER_COUNT)
      {
        if (!ft_strcmp(av[1], ssl->cipher_names[i]))
        {
          ssl->cipher_init[i](ac, av);
          break ;
        }
      }
      if (i == CIPHER_COUNT)
      {
        printf("ft_ssl: Error: '%s' is an invalid command.\n\n", av[1]);
        printf("Standard commands:\n\n");
        printf("Message Digest commands:\n");
        i = 0;
        while (i < HASH_COUNT)
        {
            printf("%s\n", ssl->hash_names[i]);
            i++;
        }
        printf("Cipher commands:");
        i = 0;
        while (i < CIPHER_COUNT)
        {
          printf("%s\n", ssl->cipher_names[i]);
          i++;
        } // MAKE STDERR!!!
        printf("\n");
        exit(1);
      }
    }
    return (0);
}