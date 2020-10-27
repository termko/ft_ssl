#include "main.h"

int b64_check_flag(t_b64 *b64, char *arg, uint32_t len)
{
  t_baseflags tmp;
  uint32_t i;

  i = 1;
  while (i < len)
  {
    if (arg[1] == 'd')
	{
		tmp.e = 0;
        tmp.d = 1;
	}
	else if (arg[1] == 'e')
	{
		tmp.e = 1;
        tmp.d = 0;
	}
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

int b64_argv_parse(t_b64 *b64, char **av)
{
	char *arg;
    uint32_t len;
    
	printf("IN FUNC:\nNOT FLAGS = %d\n ARG = %s\n", b64->not_flags, av[b64->not_flags]);
	arg = av[b64->not_flags];
	printf("%s\n", arg);
    if (!arg)
        return (0);
    len = ft_strlen(arg);
	if (!len)
		return (0);
	printf("%s\n", arg);
    if (b64->flags.o || arg[0] != '-')
	{
		if (b64->outfile != STDOUT_FILENO)
		{
			printf("Unexpected argument: %s\n", arg);
			exit(1);
		}
        return (b64_outfile_open(b64, arg));
	}
	if (b64->flags.i || arg[0] != '-')
	{
		if (b64->infile != STDIN_FILENO)
		{
			printf("Unexpected argument: %s\n", arg);
			exit(1);
		}
        return (b64_infile_open(b64, arg));
	}
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
	printf("OUTSIDE FUNC:\ni = %d\no = %d\ne = %d\nd = %d\nnot_flags = %d\narg = %s\n", b64->flags.i, b64->flags.o, b64->flags.e, b64->flags.d, b64->not_flags, av[b64->not_flags]);
	while (b64_argv_parse(b64, av))
    	b64->not_flags++;
	printf("i = %d\no = %d\ne = %d\nd = %d\n", b64->flags.i, b64->flags.o, b64->flags.e, b64->flags.d);
    if (b64->flags.i)
    {
      printf("Error, filename not found after 'i' flag\n");
      exit(-1);
    }
    if (b64->flags.o)
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

char *b64_read_file(t_b64 *b64)
{
	char *ret;

	ret = NULL;
	b64->str = ret;
	return (ret);
}

void b64_clean_decode_input(t_b64 *b64)
{
	char *str;
  char *table;
  int i;
  int len;

	b64->str = b64_read_file(b64);
	str = b64->str;
  table = b64_get_table();
  i = 0;
  len = 0;
  if (!str)
    str = ft_strdup("");
  while (str[i])
  {
    if (b64_index(table, str[i]) >= 0 || str[i] == '=')
      len++;
    i++;
  }
  if (!len)
  {
    printf("Wrong format: %s\n", str);
    exit(-1);
  }
  b64->str = (char*)malloc(sizeof(char) * (len + 1));
  if (!b64->str)
  {
    printf("Error with malloc\n");
    exit(-1);
  }
  ft_bzero(b64->str, len + 1);
  i = 0;
  len = 0;
  while (str[i])
  {
    if (b64_index(table, str[i]) >= 0 || str[i] == '=')
      b64->str[len++] = str[i];
    i++;
  }
}

void b64_decode(t_b64 *b64)
{
  char *table;
  uint32_t len;
  uint32_t iter;
  uint32_t i;
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
  b64->outlen = len * 6 / 8;
  b64->result = (char*)malloc(sizeof(char) * (b64->outlen + 1));
  ft_bzero(b64->result, b64->outlen + 1);
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
      tmp = 0;
    }
    i++;
  }
  if (i % 8 || b64->str[i / 6] == '=')
    b64->result[(i - 1) / 8] = tmp;
  printf("%s", b64->result); // get 64 \n
}

void b64_encode(t_b64 *b64)
{
  uint32_t len;
  char *table;
  uint32_t i;
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
  printf("%s", b64->result); // get 64 \n
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
  // omg its done, now for the real challenge...
  // flags are pita
  b64->infile = STDIN_FILENO;
  b64->outfile = STDOUT_FILENO;
  b64_parse_flags(b64, av);
  b64_clean_decode_input(b64);
  if (!b64->str)
    b64->str = ft_strdup("");
  // b64_encode(b64);
  b64_decode(b64);
}