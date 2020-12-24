#include "../main.h"

int md5_init(int ac, char **av)
{
    t_md5 *md5;
    void (*rounds[4])(t_md5*) = {ft_f, ft_g, ft_h, ft_i};
    int i;
    
    if (check_malloc(md5 = (t_md5*)malloc(sizeof(t_md5))))
		return (-1);
    md5->k = get_k();
    md5->s = get_s();
    i = 0;
    while (i < 4)
    {
        md5->rounds[i] = rounds[i];
        i++;
    }
	md5_parse_flags(md5, av);
	return (md5_start(md5, ac, av));
}
