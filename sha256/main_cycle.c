#include "../main.h"

void	sha256_reset_variables(t_sha256 *sha256)
{
	sha256->a = sha256->h0;
	sha256->b = sha256->h1;
	sha256->c = sha256->h2;
	sha256->d = sha256->h3;
	sha256->e = sha256->h4;
	sha256->f = sha256->h5;
	sha256->g = sha256->h6;
	sha256->h = sha256->h7;
}

void	sha256_cycle(t_sha256 *s)
{
	int i;

	i = 0;
	while (i < 64)
	{
		s->s1 = ft_rightrotate(s->e, 6) ^ ft_rightrotate(s->e, 11) ^ ft_rightrotate(s->e, 25);
		s->ch = (s->e & s->f) ^ (~(s->e) & s->g);
		s->tmp1 = s->h + s->s1 + s->ch + s->r[i] + s->w[i];
		s->s0 = ft_rightrotate(s->a, 2) ^ ft_rightrotate(s->a, 13) ^ ft_rightrotate(s->a, 22);
		s->maj = (s->a & s->b) ^ (s->a & s->c) ^ (s->b & s->c);
		s->tmp2 = s->s0 + s->maj;
		s->h = s->g;
		s->g = s->f;
		s->f = s->e;
		s->e = s->d + s->tmp1;
		s->d = s->c;
		s->c = s->b;
		s->b = s->a;
		s->a = s->tmp1 + s->tmp2;
		i++;
	}
}

void	sha256_update_variables(t_sha256 *sha256)
{
	sha256->h0 += sha256->a;
	sha256->h1 += sha256->b;
	sha256->h2 += sha256->c;
	sha256->h3 += sha256->d;
	sha256->h4 += sha256->e;
	sha256->h5 += sha256->f;
	sha256->h6 += sha256->g;
	sha256->h7 += sha256->h;
}

void	sha256_main(t_sha256 *sha256)
{
	while (sha256->void_len / 64)
	{
		sha256->w = initialize_w(sha256);
		sha256_reset_variables(sha256);
		sha256_cycle(sha256);
		sha256_update_variables(sha256);
		sha256->void_len -= 64;
		sha256->input += 64;
	}
}