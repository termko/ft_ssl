#include "../main.h"

int md5_start(t_md5 *md5, int ac, char **av)
{
    int i;
    int ret;

    ret = 0;
    i = md5->not_flags;
    while (i < ac || md5->not_flags == ac)
    {
        md5_constants(md5);
        if ((ret = md5_get_string(md5, av[i])) == -1)
			return (-1);
        if (!md5->str)
        {
            i++;
            continue ;
        }
        md5_set_length(md5);
        if (md5_prepare_message(md5))
			return (-1);
        md5_main(md5);
        md5_output(md5);
        md5_free(&md5);
        i += (md5->not_flags == ac ? 0 : ret);
        md5->not_flags = -1;
    }
	return (0);
}
