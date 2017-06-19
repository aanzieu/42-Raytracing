#include <cuda.h>
#include <stdio.h>
#include <float.h>
extern "C" {
	#include "../../../includes/display.h"
	#include "../../../includes/vectors.h"
	#include <rt.h>
	#include "gpu_rt.h"
}

#include "gpu_rt.h"

#define CUDA_ERROR_CHECK

#define CudaSafeCall( err ) __cudaSafeCall( err, __FILE__, __LINE__ )

#define CudaCheckError()    __cudaCheckError( __FILE__, __LINE__ )

inline void __cudaSafeCall( cudaError err, const char *file, const int line )
{
#ifdef CUDA_ERROR_CHECK
    if ( cudaSuccess != err )
    {
        fprintf( stderr, "cudaSafeCall() failed at %s:%i : %s\n",
                 file, line, cudaGetErrorString( err ) );
        exit( -1 );
    }
#endif

    return;
}

inline void __cudaCheckError( const char *file, const int line )
{
#ifdef CUDA_ERROR_CHECK
    cudaError err = cudaGetLastError();
    if ( cudaSuccess != err )
    {
        fprintf( stderr, "cudaCheckError() failed at %s:%i : %s\n",
                 file, line, cudaGetErrorString( err ) );
        exit( -1 );
    }

    // // More careful checking. However, this will affect performance.
    // // Comment away if needed.
    // err = cudaDeviceSynchronize();
    // if( cudaSuccess != err )
    // {
    //     fprintf( stderr, "cudaCheckError() with sync failed at %s:%i : %s\n",
    //              file, line, cudaGetErrorString( err ) );
    // //     exit( -1 );
    // }
#endif

    return;
}

__global__ void test(int *a, unsigned int constw, unsigned int consth, t_world world)
{	
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int index = row * constw + col;
	a[index] = ray_tracer(world, col, row);
}

extern "C" void render_cuda(int *a_h, unsigned int constw, unsigned int consth, t_world world, int reset)
{
	int				i;
	int 			j;
	static int 		*a_d;
	int 			y;
	int				x;
	static t_sphere	*spheres_d;
	static t_plane		*planes_d;
	static t_cylinder	*cylinders_d;
	static t_cone		*cones_d;
	static t_light		*lights_d;
	static t_paraboloid	*paraboloids_d;
	static size_t	size = 0;
	dim3		threads_per_block(32, 32);
	dim3		grid_size(constw / threads_per_block.x, consth / threads_per_block.y);


	if (reset == 0)
	{
		if (size == 0)
		{
			size = constw * consth * sizeof(int);
			CudaSafeCall(cudaMalloc(&a_d, size));
			CudaSafeCall(cudaMalloc(&spheres_d, sizeof(t_sphere) * world.spheres_len));
			CudaSafeCall(cudaMalloc(&planes_d, sizeof(t_plane) * world.planes_len));
			CudaSafeCall(cudaMalloc(&cylinders_d, sizeof(t_cylinder) * world.cylinders_len));
			CudaSafeCall(cudaMalloc(&cones_d, sizeof(t_cone) * world.cones_len));
			CudaSafeCall(cudaMalloc(&lights_d, sizeof(t_light) * world.lights_len));
			CudaSafeCall(cudaMalloc(&paraboloids_d, sizeof(t_paraboloid) * world.paraboloids_len));
		}
		CudaSafeCall(cudaMemcpy(spheres_d, world.spheres, sizeof(t_sphere) * world.spheres_len, cudaMemcpyHostToDevice));
		world.spheres = spheres_d;
		CudaSafeCall(cudaMemcpy(planes_d, world.planes, sizeof(t_plane) * world.planes_len, cudaMemcpyHostToDevice));
		world.planes = planes_d;
		CudaSafeCall(cudaMemcpy(cylinders_d, world.cylinders, sizeof(t_cylinder) * world.cylinders_len, cudaMemcpyHostToDevice));
		world.cylinders = cylinders_d;
		CudaSafeCall(cudaMemcpy(cones_d, world.cones, sizeof(t_cone) * world.cones_len, cudaMemcpyHostToDevice));
		world.cones = cones_d;
		CudaSafeCall(cudaMemcpy(lights_d, world.lights, sizeof(t_light) * world.lights_len, cudaMemcpyHostToDevice));
		world.lights = lights_d;
		CudaSafeCall(cudaMemcpy(paraboloids_d, world.paraboloids, sizeof(t_paraboloid) * world.paraboloids_len, cudaMemcpyHostToDevice));
		world.paraboloids = paraboloids_d;
		test <<< grid_size, threads_per_block>>> (a_d, constw, consth, world);
		// printf("Frame rendered\n");
		CudaCheckError();
		CudaSafeCall(cudaMemcpy(a_h, a_d, size, cudaMemcpyDeviceToHost));
		i = 0;
		y = 0;
		while (i < WIN_HEIGHT)
		{
			j = 0;
			x = 0;
			while (j < WIN_WIDTH)
			{
				pixel_to_image(world.window.screen, j, i, a_h[y * constw + x]);
				j++;
				if (j % world.render_factor == 0)
					x++;
			}
			i++;
			if (i % world.render_factor == 0)
				y++;
		}
	}
	else
	{
		cudaFree(spheres_d);
		cudaFree(planes_d);
		cudaFree(cylinders_d);
		cudaFree(cones_d);
		cudaFree(lights_d);
		cudaFree(paraboloids_d);
		cudaFree(a_d);
	}
}
