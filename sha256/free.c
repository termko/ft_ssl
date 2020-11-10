#include "../main.h"

void	sha256_free(t_sha256 **sha256)
{
	if ((*sha256)->str)
		free((*sha256)->str);
	(*sha256)->str = NULL;
	if ((*sha256)->file)
		free((*sha256)->file);
	(*sha256)->file = NULL;
}