#include "main.h"

int b64_check_flag(t_b64 *b64, char *arg, uint32_t len)
{
  t_baseflags tmp;
  uint32_t i;

  i = 0;
  while (i < len)
  {
    if (arg[1] == 'd')
        tmp.d = 1;
    else if (arg[1] == 'e')
        tmp.e = 1;
    else if (arg[1] == 'i')
    {
        if (i + 1 != len)
        {
          printf("Wrong flag format: %s\n", arg);
          exit(-1);
        }
        tmp.i = 1;
    }
    else if (arg[1] == 'o')
    {
        if (i + 1 != len)
        {
          printf("Wrong flag format: %s\n", arg);
          exit(-1);
        }
        tmp.o = 1;
    }
    else
        return (0);
    i++;
  }
  b64->flags.d = tmp.d;
  b64->flags.e = tmp.e;
  b64->flags.i = tmp.i;
  b64->flags.o = tmp.o;
  return (1);
}

int b64_outfile_open(t_b64 *b64, char *file)
{
  int fd;
  char c;

  fd = open(file, O_WRONLY);
  if (fd < 0)
  {
    printf("Error opening file %s\n", file);
    exit(-1);
  }
  if (write(fd, &c, 0) < 0)
  {
    printf("Error writing to file %s\n", file);
    exit(-1);
  }
  b64->outfile = fd;
  return (1);
}

int b64_infile_open(t_b64 *b64, char *file)
{
  int fd;
  char c;
  fd = open(file, O_RDONLY);
  if (fd < 0)
  {
    printf("Error opening file %s\n", file);
    exit(-1);
  }
  if (read(fd, &c, 0) < 0)
  {
    printf("Error reading file %s\n", file);
    exit(-1);
  }
  b64->infile = fd;
  return (1);
}

int b64_argv_parse(t_b64 *b64, char *arg)
{
    uint32_t len;
    
    if (!arg)
        return (0);
    len = ft_strlen(arg);
    if (!len)
        return (0);
    if (b64->flags.no)
        return (b64_outfile_open(b64, arg));
    if (b64->flags.ni)
        return (b64_infile_open(b64, arg));
    if (arg[0] != '-')
        return (0);
    if (b64_check_flag(b64, arg, len))
        return (1);
    
    return (1);
}

void b64_parse_flags(t_b64 *b64, char **av)
{
    b64->not_flags = 2;
    b64->flags.d = 0;
    b64->flags.e = 0;
    b64->flags.i = 0;
    b64->flags.o = 0;
    b64->flags.no = 0;
    b64->flags.ni = 0;
    while (b64_argv_parse(b64, av[b64->not_flags]))
        b64->not_flags++;
    if (b64->flags.ni)
    {
      printf("Error, filename not found after 'i' flag\n");
      exit(-1);
    }
    if (b64->flags.no)
    {
      printf("Error, filename not found after 'o' flag\n");
      exit(-1);
    }
    if (!b64->flags.d)
      b64->flags.e = 1;
    b64->out.d = b64->flags.d;
    b64->out.e = b64->flags.e;
    b64->out.i = b64->flags.i;
    b64->out.o = b64->flags.o;
}

int b64_index(char *table, char c)
{
  int index;

  index = 0;
  while (index < 64)
  {
    if (table[index] == c)
      return (index);
    index++;
  }
  return (-1);
}

char *b64_get_table(void)
{
  static char table[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '/'
  };

  return (table);
}

char *b64_clean_decode_input(t_b64 *b64, char *str)
{
  char *table;
  char *ret;
  int i;
  int len;

  table = b64_get_table();
  i = 0;
  len = 0;
  while (str[i])
  {
    if (b64_index(table, str[i]) >= 0 || str[i] == '=')
      len++;
    i++;
  }
  ret = (char*)malloc(sizeof(char) * (len + 1));
  if (!ret)
  {
    printf("Error with malloc\n");
    exit(-1);
  }
  ft_bzero(ret, len + 1);
  i = 0;
  len = 0;
  while (str[i])
  {
    if (b64_index(table, str[i]) >= 0 || str[i] == '=')
      ret[len++] = str[i];
    i++;
  }
  return (ret);
}

void b64_decode(t_b64 *b64)
{
  char *table;
  uint32_t len;
  uint32_t outlen;
  uint32_t iter;
  int i;
  char tmp;
  int index;
  int bit;

  table = b64_get_table();
  len = ft_strlen(b64->str);
  if (len % 4)
  {
    printf("Wrong format: %s\n", b64->str);
    exit(-1);
  }
  outlen = len * 6 / 8;
  b64->result = (char*)malloc(sizeof(char) * (outlen + 1));
  ft_bzero(b64->result, outlen + 1);
  tmp = 0;
  i = 0;
  iter = 0;
  while (i < len * 6 && iter < len)
  {
    if (!(i % 6))
    {
      if (b64->str[i / 6] == '=')
        break ;
      index = b64_index(table, b64->str[i / 6]);
    }
    bit = index & (1 << (5 - (i % 6)));
    tmp |= (bit ? 1 : 0) << (7 - (i % 8));
    if (!(i % 8))
    {
      b64->result[(i - 1) / 8] = tmp;
      printf("[%d] %c\n", tmp, tmp);
      tmp = 0;
    }
    i++;
  }
  if (i % 8 || b64->str[i / 6] == '=')
    b64->result[(i - 1) / 8] = tmp;
  printf("%s", b64->result);
}

void b64_encode(t_b64 *b64)
{
  uint32_t len;
  uint32_t outlen;
  char *table;
  int i;
  int tmp;
  int bit;

  table = b64_get_table();
  len = ft_strlen(b64->str);
  b64->outlen = len * 8 / 6;
  if (b64->outlen % 4)
    b64->outlen += (4 - b64->outlen % 4);
  b64->result = (char*)malloc(sizeof(char) * (b64->outlen + 1));
  ft_bzero(b64->result, b64->outlen + 1);
  if (!b64->result)
  {
    printf("Error with malloc\n");
    exit(-1);
  }
  tmp = 0;
  i = 0;
  while (i < len * 8)
  {
    bit = b64->str[i / 8] & (1 << (7 - (i % 8)));
    tmp |= (bit ? 1 : 0) << (5 - (i % 6));
    i++;
    if (!(i % 6))
    {
      b64->result[(i - 1) / 6] = table[tmp];
      tmp = 0;
    }
  }
  if (i % 6)
    b64->result[(i - 1) / 6] = table[tmp];
  i = i / 6 + 1;
  while (i < b64->outlen)
  {
    b64->result[i] = '=';
    i++;
  }
  b64->result[i] = '\0';
  printf("%s", b64->result);
}

void base64_init(int ac, char **av)
{
  t_b64 *b64;

  b64 = (t_b64*)malloc(sizeof(t_b64*));
  if (!b64)
  {
    printf("Error with malloc\n");
    exit(ac);
  }
  // b64_parse_flags(b64, av);
  // so we make memlen * 8 / 6 char array and map it to the string of 64 bytes long...
  //ok it may be easy, the only hard thing is division to 6 bits... maybe take bit by bit and iterate through 8 bits of char and then iterate through 6 bits of output... mkay, seems easy... need to see how flags work
  // encode done, decode to go, not bad huh
  // almost working, need to make sure there are no spaces, dunno how original handles it
  // omg its done, now for the real challenge...
  // flags are pita
  b64_parse_flags(b64, av);
  b64->str = b64_clean_decode_input(b64, av[2]);
  // b64_encode(b64);
  b64_decode(b64);
}