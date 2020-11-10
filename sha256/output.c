#include "../main.h"

void	sha256_hash_output(t_sha256 *sha256)
{
  printf("%08x%08x%08x%08x%08x%08x%08x%08x",
            sha256->h0, sha256->h1, sha256->h2, sha256->h3,
            sha256->h4, sha256->h5, sha256->h6, sha256->h7);
}

void	sha256_verbal_output(t_sha256 *sha256)
{
	if (sha256->out.r)
	{
		sha256_hash_output(sha256);
		if (sha256->out.s)
		{
			printf(" \"%s\"", sha256->str);
			sha256->out.s = 0;
		}
		else
			printf(" %s", sha256->file);
	}
	else
	{
		printf("SHA256(");
		if (sha256->out.s)
		{
			printf("\"%s\")= ", sha256->str);
			sha256->out.s = 0;
		}
		else
			printf("%s)= ", sha256->file);
		sha256_hash_output(sha256);
	}
}

void	sha256_output(t_sha256 *sha256)
{
    if (sha256->out.p)
    {
        printf("%s", sha256->str);
        sha256_hash_output(sha256);
        printf("\n");
        sha256->out.p = 0;
        return ;
    }
    if (!sha256->out.q)
		sha256_verbal_output(sha256);
    else
        sha256_hash_output(sha256);
    printf("\n");
}