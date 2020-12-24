#include "../main.h"

int	md5_prepare_message(t_md5 *md5)
{
	uint64_t	void_len_bits;
	uint32_t	i;

	void_len_bits = md5->append_len + md5->bits_len;
	if (md5->append_len <= 64)
		void_len_bits += 512;
	md5->void_len = void_len_bits / 8;
	if (check_malloc(md5->input = malloc(md5->void_len)))
		return (-1);
	ft_bzero(md5->input, md5->void_len);
	i = 0;
	while (i < md5->len)
	{
		((char*)(md5->input))[i] = md5->str[i];
		i++;
	}
	((char*)(md5->input))[i] = 0x80;
	((long*)md5->input)[(md5->void_len / 8) - 1] = md5->bits_len;
	return (0);
}

void	md5_set_length(t_md5 *md5)
{
	md5->bits_len = md5->len * 8;
	md5->append_len = 512 - (md5->bits_len % 512);
}

void	md5_constants(t_md5 *md5)
{
	md5->A = 1732584193;
	md5->B = 4023233417;
	md5->C = 2562383102;
	md5->D = 271733878;
}
