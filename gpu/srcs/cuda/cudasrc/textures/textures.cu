extern "C" {
	#include <rt.h>
	#include <gpu_rt.h>
	#include <vectors.h>
	#include <equation.h>
}

#pragma hd_warning_disable

__host__ __device__ Uint32 	getpixel(SDL_Surface *surface, int x, int y)
{
  int		bpp;
  Uint8 *p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  if (bpp == 1)
    return (*p);
  else if (bpp == 2)
    return (*(Uint16 *)p);
  else if (bpp == 3)
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return (p[0] << 16 | p[1] << 8 | p[2]);
    else
      return (p[0] | p[1] << 8 | p[2] << 16);
  else if (bpp == 4)
    return (*(Uint32 *)p);
	return (0);
}

__host__ __device__ t_color load_texture_at(t_texture texture, t_ray ray,\
		t_intersection *intersection, t_world world)
{
	Uint32		pixel;
	Uint8			r, g, b;
	double 		u, v;
	t_color 	ret;

	u = (0.5 + atanf(intersection->normal_v.x / -(intersection->normal_v.z
		+ SURFACE_TOLERANCE)) / (2 * M_PI)) * texture.tex->w;
	v = (0.5 - asin(intersection->normal_v.y) / M_PI) * texture.tex->h;
	u = fmod(u, (double)(texture.tex->w - 1.0));
	v = fmod(v, (double)(texture.tex->h - 1.0));
	pixel = getpixel(texture.tex, u, v);
	SDL_GetRGB(pixel, texture.tex->format, &r, &g, &b);
	ret.r = (double)(r) / 255;
	ret.g = (double)(g) / 255;
	ret.b = (double)(b) / 255;
	return (ret);
}