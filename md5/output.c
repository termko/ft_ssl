#include "../main.h"

void	md5_hash_output(t_md5 *md5)
{
	printf("%08x%08x%08x%08x",
		btol(md5->A), btol(md5->B), btol(md5->C), btol(md5->D));
}

void	md5_verbal_output(t_md5 *md5)
{
	if (md5->out.r)
	{
		md5_hash_output(md5);
		if (md5->out.s)
		{
			printf(" \"%s\"", md5->str);
			md5->out.s = 0;
		}
		else
			printf(" %s", md5->file);
	}
	else
	{
		printf("MD5(");
		if (md5->out.s)
		{
			printf("\"%s\")= ", md5->str);
			md5->out.s = 0;
		}
		else
			printf("%s)= ", md5->file);
		md5_hash_output(md5);
	}
}

void	md5_output(t_md5 *md5)
{
    if (md5->out.p)
    {
		printf("%s", md5->str);
		md5_hash_output(md5);
		printf("\n");
		md5->out.p = 0;
		return ;
	}
	if (!md5->out.q)
		md5_verbal_output(md5);
	else
		md5_hash_output(md5);
	printf("\n");
}