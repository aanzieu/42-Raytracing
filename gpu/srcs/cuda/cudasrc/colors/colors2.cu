
extern "C" {
	#include "../../cudaheader/gpu_rt.h"
}

//__host__ __device__ t_color color_divide(t_color color, int coef)
//{
//	return ((t_color){color.r / coef, color.g / coef, color.b / coef});
//}

__host__ __device__ t_color	int_to_rgb(int color)
{
	t_color	rgb_color;

	if (color > 16777215)
		color = 16777215;
	rgb_color.b = color & 255;
	rgb_color.g = (color >> 8) & 255;
	rgb_color.r = (color >> 16) & 255;
	return (rgb_color);
}

__host__ __device__	int	rgb_to_int(t_color color)
{
	return ((((int)(color.r)&0x0ff)<<16)|(((int)(color.g)&0x0ff)<<8)|((int)(color.b)&0x0ff));
}