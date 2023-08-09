// # include <mlx.h>
// # include <X11/keysym.h>
// # include <X11/X.h>
// # include <stdlib.h>

// # define WIN_WIDTH	800
// # define WIN_HEIGHT 600

// int main(void)
// {
//     void    *mlx;
//     void    *win;
//     void    *img;
//     char    *relative_path = "./NO.xmp";
//     int     img_width = 400;
//     int     img_height = 400;
//     char	*addr;
//     int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;

//     mlx = mlx_init();
//     win = mlx_new_window(mlx, 1000, 500, "test");
//     img = mlx_xpm_file_to_image(mlx, "./NO.xpm", &img_width, &img_height);
//     if(img == NULL)
//         exit(120);

//     mlx_put_image_to_window(mlx, win, img, 0, 0);
//     while(1);
//     return(0);
// }
#include <stdio.h>
#include <mlx.h>
#include <stdlib.h>

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			largura;
	int			altura;


	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->data + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int main()
{
		void	*mlx;
		void	*win;
		t_img	img1;
		int **buffer;
		int x;
		int y;
		int pixel_index;

		mlx = mlx_init();
		img1.ptr = mlx_xpm_file_to_image(mlx, "./SO.xpm", &img1.largura, &img1.altura);
		img1.data = (int *)mlx_get_data_addr(img1.ptr, &img1.bpp, &img1.size_l, &img1.endian);

		buffer = (int **)malloc(sizeof(int *) * img1.altura);
		y = -1;
		while(++y < img1.altura)
    	{
			buffer[y] = (int *)malloc(sizeof(int) * img1.largura);
   			x = -1;
			while(++x < img1.largura)
			{
				pixel_index = y * img1.largura + x;
				buffer[y][x] = img1.data[pixel_index];
			}
		}
		printf("pixel_color=%i\n", buffer[63][35]);
		y = -1;
		while (++y < img1.altura)
			free(buffer[y]);
		free(buffer);

		return (0);
}
