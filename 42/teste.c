#include "minilibx/mlx.h"
#include <stdio.h>

int main(void)
{
    void *mlx;
    void *img;
    char *path = "./stonewall.xpm";
    char *addr;
    int img_w;
    int img_h;
    int bbp;
    int sizeln;
    int endian;

    img = NULL;
    mlx = mlx_init();
    img = mlx_xpm_file_to_image(mlx, path, &img_w, &img_h);
    addr = mlx_get_data_addr(img, &bbp, &sizeln, &endian);
    printf("%p\n", img);
    printf("%p\n", addr);
    if (img == NULL)
        printf("not funfou\n");
    else
        printf("funfou\n");
    
}