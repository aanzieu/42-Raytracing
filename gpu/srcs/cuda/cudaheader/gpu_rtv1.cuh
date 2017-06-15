#ifndef CUDA_MD_H
# define CUDA_MD_H
#ifndef CUDA_HOSTDEV
# ifdef __CUDA_ARCH__
# define CUDA_HOSTDEV __host__ __device__
# else
# define CUDA_HOSTDEV
# endif
#endif

CUDA_HOSTDEV int	ray_tracer(t_world world, int x, int y);

#endif
