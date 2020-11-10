#include "../main.h"

void	ft_f(t_md5 *md5)
{
    md5->f = ((md5->B & md5->C) | (~(md5->B) & md5->D));
    md5->g = md5->i;
}

void	ft_g(t_md5 *md5)
{
    md5->f = ((md5->B & md5->D) | (md5->C & ~(md5->D)));
    md5->g = (5 * md5->i + 1) % 16;;
}

void	ft_h(t_md5 *md5)
{
    md5->f = (md5->B ^ md5->C ^ md5->D);
    md5->g = (3 * md5->i + 5) % 16;
}

void	ft_i(t_md5 *md5)
{
    md5->f = (md5->C ^ (md5->B | ~(md5->D)));
    md5->g = (7 * md5->i) % 16;
}