#include "main.h"

uint32_t	ft_leftrotate(uint32_t what, uint32_t to)
{
    return ((uint32_t)((what << to) | (what >> (32 - to))));
}

uint32_t	ft_rightrotate(uint32_t what, uint32_t to)
{
    return ((uint32_t)((what >> to) | (what << (32 - to))));
}