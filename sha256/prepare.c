#include "../main.h"

void	sha256_set_length(t_sha256 *sha256)
{
	sha256->bits_len = sha256->len * 8;
	sha256->append_len = 512 - (sha256->bits_len % 512);
}

void	prepare_length(void *input, uint32_t len, uint64_t len_bits)
{
    void	*tmp;
    int		i;

	i = 0;
	tmp = &(len_bits);
	while (i < 8)
	{
		((char*)input)[len - 8 + i] =
				((char*)tmp)[7 - i];
		i++;
	}
}

void	sha256_prepare_message(t_sha256 *sha256)
{
	uint64_t	void_len_bits;
	uint32_t	i;

	void_len_bits = sha256->append_len + sha256->bits_len;
	if (sha256->append_len <= 64)
		void_len_bits += 512;
	sha256->void_len = void_len_bits / 8;
	sha256->input = malloc(sha256->void_len);
	if (!(sha256->input))
	{
		ft_putstr("Malloc Error\n");
		exit(-1);
	}
	ft_bzero(sha256->input, sha256->void_len);
	i = 0;
	while (i < sha256->len)
	{
		((char*)(sha256->input))[i] = sha256->str[i];
		i++;
	}
	((char*)(sha256->input))[i] = 0x80;
	prepare_length(sha256->input, sha256->void_len, sha256->bits_len);
}

void	sha256_constants(t_sha256 *sha256)
{
	sha256->h0 = 0x6a09e667;
	sha256->h1 = 0xbb67ae85;
	sha256->h2 = 0x3c6ef372;
	sha256->h3 = 0xa54ff53a;
	sha256->h4 = 0x510e527f;
	sha256->h5 = 0x9b05688c;
	sha256->h6 = 0x1f83d9ab;
	sha256->h7 = 0x5be0cd19;
}
