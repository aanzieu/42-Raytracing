#include <cuda.h>
#include <stdio.h>
#include <float.h>

extern "C" {
#include "../../../includes/display.h"
#include "../../../includes/vectors.h"
#include "../../../includes/rt.h"
#include "../cudaheader/gpu_rt.h"
}


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
		exit(-1);
	}
#endif
	return;
}


void checkCUDAError(const char *msg) {
  cudaError_t err = cudaGetLastError();
  if( cudaSuccess != err) {
    fprintf(stderr, "Cuda error: %s: %s.\n", msg, cudaGetErrorString( err) ); 
	system("pause");
    exit(EXIT_FAILURE); 
  }
} 

//inline void __cudaCheckError( const char *file, const int line )
//{
//#ifdef CUDA_ERROR_CHECK
//	cudaError err = cudaGetLastError();
//	if (cudaSuccess != err)
//	{
//		fprintf( stderr, "cudaCheckError() failed at %s:%i : %s\n",
//				file, line, cudaGetErrorString( err ) );
//		exit( -1 );
//	}
//#endif
//	return;
//}

__host__ __device__ void 	color_scal(t_color *c1, double coef)
{
	c1->r *= coef;
	c1->g *= coef;
	c1->b *= coef;
}

__host__ __device__	void	color_sum(t_color *c1, t_color *c2)
{
	c1->r += c2->r;
	c1->g += c2->g;
	c1->b += c2->b;
}


__host__ __device__ void apply_recurse(t_world *world, t_ray *ray,
	t_intersection *intersection, t_color *color, int depth)
{
	if (depth > MAX_DEPTH) {
		color->r = 0; 
		color->g = 0;
		color->b = 0;
		return ;
	}
	else {
		if (intersection->transparence_coef > 0) {
		
			t_intersection intersection_tmp;
			t_ray			ray_tmp;

			ray_tmp.origin = intersection->pos;
			ray_tmp.dir = ray->dir;
			get_closest_intersection(*world, ray_tmp, &intersection_tmp);
			color_scal(color, 1 - intersection->transparence_coef);
			apply_recurse(world, &ray_tmp, &intersection_tmp, color, depth + 1);
		}
	}
}


__global__ void test_recursive_cuda(int *a, unsigned int constw, unsigned int consth, t_world *world, int depth)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int index = row * constw + col;

	t_ray	ray;
	t_intersection intersection;

	new_intersection(&intersection);
	get_up_left(world);
	get_ray_direction(*world, &ray, col, row);

	t_color					color;
	int							i;

	i = 0;
	color = new_color(0, 0, 0);
	if (get_closest_intersection(*world, ray, &intersection)) {
			//if(world.keys.light_none == 1 && world.mode == 0)
			//	apply_recurse(world, &ray, &intersection, &color, depth);

			color = color_multiply(color, world->ambient.color);
			color = color_scalar(color, world->ambient.intensity);
			if(world->keys.light_none == 0)
				color = intersection.color;
		//	if(world.keys.select == 1)
		//		cartoon_effect(world, &color, world.lights[i], intersection, ray);
			while (i < world->lights_len && world->keys.light_none == 1)
			{
				color = get_light_at(*world, color, world->lights[i], intersection, ray);
		//		if (world.keys.pad_0 == 6)
		//			cartoon_effect(world, &color, world.lights[i], intersection, ray);
				i++;
			}
		}
//}
	a[index] = get_color(color);
}



//__global__ void test(int *a, unsigned int constw, unsigned int consth, t_world world)
//{
//	int col = blockIdx.x * blockDim.x + threadIdx.x;
//	int row = blockIdx.y * blockDim.y + threadIdx.y;
//	int index = row * constw + col;
//	a[index] = ray_tracer(world, col, row + world.offsets.y_min);
//}

extern "C" void render_cuda(int *a_h, unsigned int constw, unsigned int consth, t_world *world, int reset)
{
	int 		*a_d = 0;
	t_sphere	*spheres_d = NULL;
	t_plane		*planes_d = NULL;
	t_cylinder	*cylinders_d = NULL;
	t_cone		*cones_d = NULL;
	t_light		*lights_d = NULL;
	// static t_paraboloid	*paraboloids_d;
	
	dim3		threads_per_block(32, 32);
	dim3		grid_size(constw / threads_per_block.x, consth / threads_per_block.y);

	//*****   init size of map    ******

	size_t		size = 0;
	size = constw * consth * sizeof(int);
	cudaMalloc(&a_d, size);

	int	depth = 1;
	//*****   mcudamalloc obj   ******

	cudaMalloc(&spheres_d, sizeof(t_sphere) * world->spheres_len);
	cudaMalloc(&planes_d, sizeof(t_plane) * world->planes_len);
	cudaMalloc(&cylinders_d, sizeof(t_cylinder) * world->cylinders_len);
	cudaMalloc(&cones_d, sizeof(t_cone) * world->cones_len);
	cudaMalloc(&lights_d, sizeof(t_light) * world->lights_len);

	cudaMemcpy(spheres_d, world->spheres, sizeof(t_sphere) * world->spheres_len, cudaMemcpyHostToDevice);
//		world.spheres = spheres_d;
	cudaMemcpy(planes_d, world->planes, sizeof(t_plane) * world->planes_len, cudaMemcpyHostToDevice);
//		world.planes = planes_d;
	cudaMemcpy(cylinders_d, world->cylinders, sizeof(t_cylinder) * world->cylinders_len, cudaMemcpyHostToDevice);
//		world.cylinders = cylinders_d;
	cudaMemcpy(cones_d, world->cones, sizeof(t_cone) * world->cones_len, cudaMemcpyHostToDevice);
//		world.cones = cones_d;
	cudaMemcpy(lights_d, world->lights, sizeof(t_light) * world->lights_len, cudaMemcpyHostToDevice);
//		world.lights = lights_d;
	

	//size_t limits;
  	//cudaDeviceSetLimit(cudaLimitStackSize, 1024*sizeof(float));
  	//cudaDeviceGetLimit(&limits, cudaLimitStackSize);

//	checkCUDAError("pre-raytraceRay error");

	//test <<< grid_size, threads_per_block>>> (a_d, constw, consth, world);

	test_recursive_cuda <<< grid_size, threads_per_block>>> (a_d, constw, consth, world, depth);
//	checkCUDAError("raytraceRay error");

	cudaMemcpy(a_h, a_d, size, cudaMemcpyDeviceToHost);

 	//free up stuff, or else we'll leak memory like a madman	
//	if(spheres_d != NULL)
		cudaFree(spheres_d);
//	 if(planes_d != NULL)
	 	cudaFree(planes_d);
//	if(cones_d != NULL)
		cudaFree(cones_d);
//	if(cylinders_d != NULL)
		cudaFree(cylinders_d);
//	if(lights_d != NULL)
		cudaFree(lights_d);
	//if(a_d != NULL)
		cudaFree(a_d);

	cudaThreadSynchronize();
//	checkCUDAError("Kernel Error");
}