#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

typedef struct  s_opt
{
	int ac;
	char **av;
	char *avail;
	int pos;
	char *arg;
}               t_opt;