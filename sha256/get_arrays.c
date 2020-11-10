#include "../main.h"

uint32_t	sha256_get_uint32(t_sha256 *sha256, int i)
{
	int				j;
	unsigned char	num[4];

	j = 0;
	while (j < 4)
	{
		num[j] = ((unsigned char*)(sha256->input))[j + i * 4];
		j++;
	}
	return ((uint32_t)(num[0] << 24 | num[1] << 16 | num[2] << 8 | num[3]));
}

uint32_t	*initialize_w(t_sha256 *sha256)
{
	static uint32_t	w[64];
	int				i;

	i = 0;
	while (i < 16)
	{
		w[i] = sha256_get_uint32(sha256, i);
		i++;
	}
	while (i < 64)
	{
		sha256->s0 = (ft_rightrotate(w[i - 15], 7) ^
			ft_rightrotate(w[i - 15], 18) ^ (w[i - 15] >> 3));
		sha256->s1 = (ft_rightrotate(w[i - 2], 17) ^
			ft_rightrotate(w[i - 2], 19) ^ (w[i - 2] >> 10));
		w[i] = w[i - 16] + sha256->s0 + w[i - 7] + sha256->s1;
		i++;
	}
	return (w);
}

uint32_t	*get_r(void)
{
	static uint32_t r[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	return (r);
}