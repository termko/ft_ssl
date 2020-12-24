#include "main.h"

int	ft_usage(void)
{
	//printf("usage: ft_ssl command [command opts] [command args]\n"); // STDERR WITH FPRINTF
	ft_putstr("PLACEHOLDER\n");
	return (-1);
}

int	wrong_command(t_ssl *ssl, char *str)
{
	int	i;

	//printf("ft_ssl: Error: '%s' is an invalid command.\n\n", str); // STDERR WITH FPRINTF
	//printf("Standard commands:\n\n");
	//printf("Message Digest commands:\n");
	ft_putstr("PLACEHOLDER\n");
	i = 0;
	while (i < HASH_COUNT)
	{
		ft_putstr("PLACEHOLDER\n");
		//printf("%s\n", ssl->hash_names[i]);
		i++;
	}
	ft_putstr("PLACEHOLDER\n");
	(void)ssl;
	(void)str;
	//printf("Cipher commands:\n");
	return (-1);
	// MAKE EVERY PLACEHOLDER A STDERR
}
