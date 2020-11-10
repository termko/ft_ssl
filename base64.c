#include "main.h"

int b64_check_flag(t_b64 *b64, char *arg, uint32_t len)
{
  t_baseflags tmp;
  uint32_t i;

  i = 1;
  tmp.o = b64->flags.o;
  tmp.i = b64->flags.i;
  tmp.e = b64->flags.e;
  tmp.d = b64->flags.d;
  tmp.c = b64->flags.c;
  while (i < len)
  {
    if (arg[i] == 'd')
	{
		tmp.e = 0;
        tmp.d = 1;
	}
	else if (arg[i] == 'e')
	{
		tmp.e = 1;
        tmp.d = 0;
	}
	else if (arg[i] == 'c')
		tmp.c = 1;
    else if (arg[i] == 'i')
    {
        if (i + 1 != len)
        {
          printf("Wrong flag format: %s\n", arg);
          exit(-1);
        }
        tmp.i = 1;
    }
    else if (arg[i] == 'o')
    {
        if (i + 1 != len)
        {
          printf("Wrong flag format: %s\n", arg);
          exit(-1);
        }
        tmp.o = 1;
    }
    else
    {
		printf("Unexpected flag: %c\n", arg[i]);
		exit(1);
	}
    i++;
  }
  b64->flags.d = tmp.d;
  b64->flags.e = tmp.e;
  b64->flags.i = tmp.i;
  b64->flags.o = tmp.o;
  b64->flags.c = tmp.c;
  return (1);
}

int b64_outfile_open(t_b64 *b64, char *file)
{
  int fd;
  char c;

  fd = open(file, O_WRONLY | O_CREAT);
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
    
	arg = av[b64->not_flags];
    if (!arg)
        return (0);
    len = ft_strlen(arg);
	if (!len)
		return (0);
    if (b64->flags.o) // || arg[0] != '-')
	{
		if (b64->outfile != STDOUT_FILENO)
		{
			printf("Unexpected argument: %s\n", arg);
			exit(1);
		}
		b64->flags.o = 0;
        return (b64_outfile_open(b64, arg));
	}
	if (b64->flags.i) // || arg[0] != '-')
	{
		if (b64->infile != STDIN_FILENO)
		{
			printf("Unexpected argument: %s\n", arg);
			exit(1);
		}
		b64->flags.i = 0;
        return (b64_infile_open(b64, arg));
	}
	if (arg[0] != '-')
    {
		printf("Unexpected argument: %s\n", arg);
		exit(1);
	}
    if (!b64_check_flag(b64, arg, len))
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
	b64->flags.c = 0;
	while (b64_argv_parse(b64, av))
    	b64->not_flags++;
	// printf("Exit while on not_flags = %d arg = %s\n", b64->not_flags, av[b64->not_flags]);
	// printf("i = %d\no = %d\ne = %d\nd = %d\nc = %d\n", b64->flags.i, b64->flags.o, b64->flags.e, b64->flags.d, b64->flags.c);
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

void b64_clean_decode_input(t_b64 *b64)
{
  char *table;
  char *tmp;
  size_t i;
  int len;

	tmp = b64->str;
  table = b64_get_table();
  i = 0;
  len = 0;
  while (i < b64->len)
  {
    if (b64_index(table, b64->str[i]) >= 0 || b64->str[i] == '=')
      len++;
    i++;
  }
  if (!len)
  {
    printf("Wrong format: %s\n", b64->str);
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
  while (b64->str[i])
  {
    if (b64_index(table, tmp[i]) >= 0 || tmp[i] == '=')
      b64->str[len++] = tmp[i];
    i++;
  }
  free(tmp);
}

void b64_decode(t_b64 *b64)
{
  char *table;
  uint32_t iter;
  uint32_t i;
  char tmp;
  int index;
  int bit;

  table = b64_get_table();
  if (b64->len % 4)
  {
	printf("You can't be here, can ya..?\n%lu\n", b64->len);
    printf("Wrong format: %s\n", b64->str);
    exit(-1);
  }
  b64->outlen = b64->len * 6 / 8;
  b64->result = (char*)malloc(sizeof(char) * (b64->outlen + 1));
  ft_bzero(b64->result, b64->outlen + 1);
  tmp = 0;
  i = 0;
  iter = 0;
  while (i < b64->len * 6 && iter < b64->len)
  {
    if (!(i % 6))
    {
      if (b64->str[i / 6] == '=')
        break ;
      index = b64_index(table, b64->str[i / 6]);
    }
    bit = index & (1 << (5 - (i % 6)));
    tmp |= (bit ? 1 : 0) << (7 - (i % 8));
    if (!(i % 8) && i != 0)
    {
      b64->result[(i - 1) / 8] = tmp;
	  tmp = 0;
    }
    i++;
  }
  if (!(i % 8) || b64->str[i / 6] == '=')
    b64->result[(i - 1) / 8] = tmp;
  write(b64->outfile, b64->result, b64->outlen);
  write(STDERR_FILENO, b64->result, b64->outlen);
  write(STDERR_FILENO, "dec done\n", 9);
}

void b64_encode(t_b64 *b64)
{
  char *table;
  uint32_t i;
  int tmp;
  int bit;

  table = b64_get_table();
  b64->outlen = b64->len * 8 / 6;
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
  while (i < b64->len * 8)
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
  write(b64->outfile, b64->result, b64->outlen);
  write(STDERR_FILENO, b64->result, b64->outlen);
  write(STDERR_FILENO, "enc done\n", 9);
}

void b64_read_input(t_b64 *b64)
{
	char tmp[1024];
	size_t i;
	int got;
	
	b64->len = 0;
    b64->str = NULL;
    ft_bzero(tmp, sizeof(char) * 1024);
    i = 1;
    while ((got = read(b64->infile, tmp, 1024)) > 0)
    {
        if (!b64->str)
            b64->str = ft_memdup(tmp, got);
        else
            b64->str = ft_realloc(&(b64->str), tmp, b64->len, got);
        ft_bzero(tmp, 1024);
        b64->len += got;
        i++;
    }
	if (!b64->str)
		b64->str = ft_strdup("");
	if (b64->infile != STDIN_FILENO)
		close(b64->infile);
	if (b64->flags.c && b64->flags.d)
		b64_clean_decode_input(b64); // wtf is here...
}

void base64_init(int ac, char **av)
{
  t_b64 *b64;

  b64 = (t_b64*)malloc(sizeof(t_b64));
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
//   b64_clean_decode_input(b64);
	// if (!b64->str)
	// 	b64->str = ft_strdup("");
	b64_read_input(b64);

	// im lost totally, wtf, it cant be so hard lmao...
	// if (b64->flags.e)
  	// 	b64_encode(b64);
	// else
	// 	b64_decode(b64);
}