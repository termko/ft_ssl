#include "../main.h"

void	md5_reset_variables(t_md5 *md5)
{
	md5->aa = md5->A;
	md5->bb = md5->B;
	md5->cc = md5->C;
	md5->dd = md5->D;
	md5->i = 0;
}

void	md5_update_variables(t_md5 *md5)
{
	md5->A += md5->aa;
	md5->B += md5->bb;
	md5->C += md5->cc;
	md5->D += md5->dd;
	md5->void_len -= 64;
	md5->input += 64;
}

void	md5_cycle(t_md5 *md5)
{
	while (md5->i < 64)
	{
		md5->rounds[md5->i / 16](md5);
		md5->tmp = md5->D;
		md5->D = md5->C;
		md5->C = md5->B;
		md5->B += ft_leftrotate(md5->A + md5->f + md5->k[md5->i] +
				((uint32_t*)md5->input)[md5->g], md5->s[md5->i]);
		md5->A = md5->tmp;
		md5->i++;
	}
}

void	md5_main(t_md5 *md5)
{
	while (md5->void_len / 64)
	{
		md5_reset_variables(md5);
		md5_cycle(md5);
		md5_update_variables(md5);
	}
}