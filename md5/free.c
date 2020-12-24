#include "../main.h"

void md5_free(t_md5 **md5)
{
	if ((*md5)->str)
		free((*md5)->str);
	(*md5)->str = NULL;
	if ((*md5)->file)
		free((*md5)->file);
	(*md5)->file = NULL;
}
