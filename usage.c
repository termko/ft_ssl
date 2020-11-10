#include "main.h"

void	ft_usage(void)
{
	printf("usage: ft_ssl command [command opts] [command args]\n");
	exit(-1);
}

void	wrong_command(t_ssl *ssl, char *str)
{
	int	i;

	printf("ft_ssl: Error: '%s' is an invalid command.\n\n", str);
	printf("Standard commands:\n\n");
	printf("Message Digest commands:\n");
	i = 0;
	while (i < HASH_COUNT)
	{
		printf("%s\n", ssl->hash_names[i]);
		i++;
	}
	printf("Cipher commands:\n");
	exit(-1);
}