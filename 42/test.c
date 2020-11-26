#include <stdio.h>
#include <mlx.h>
#include "functions.c"
#include "constants.c"



int main(void)
{
    void    
    void    *img;
    t_data  img;

    mlx = mlx_init();
    img.img = mlx_new_image(mlx, 640, 480);

    img.addr = mlx_get_data_addr(img.img, &.img.bit_per_pixel, 
                                 &img.line_length, &img.endian);
    
    // // test bitwise function
    // int num = 0;

    // num = ft_crt_trgb(255,0,0,0);
    // printf("0x%08X\n", num);

    return (0);
}