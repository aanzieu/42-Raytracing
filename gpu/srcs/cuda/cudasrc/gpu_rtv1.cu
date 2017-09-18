#include <cuda.h>
#include <stdio.h>
#include <float.h>
//#include "./cuPrintf.cu"

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

// __global__ void sendImageToWorld(int* a_h, int x, int y, int *a_d)
// {
//
//   int xx = (blockIdx.x * blockDim.x) + threadIdx.x;
//   int yy = (blockIdx.y * blockDim.y) + threadIdx.y;
//   int index = xx + (yy * x);
//
//   if(xx <= x && yy <= y)
//     a_h[index] = a_d[index];
// }

__global__ void test(int *a, unsigned int constw, unsigned int consth, t_world world)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int index = row * constw + col;
	int yy = world.aa * row + world.offsets.y_min; 					//thread->y_max * thread->world->aa + world.offsets.y_min);
	int xx = world.aa * col; //
	// if (col < constw && row < consth)
		a[index] = ray_tracer_gpu(world, xx, yy);// + world.offsets.y_min);
}



//__global__ void test(int *a, unsigned int constw, unsigned int consth, t_world world)
//{
//	int col = blockIdx.x * blockDim.x + threadIdx.x;
//	int row = blockIdx.y * blockDim.y + threadIdx.y;
//	int index = row * constw + col;
//	a[index] = ray_tracer(world, col, row + world.offsets.y_min);
//}

extern "C" void render_cuda(int *a_h, unsigned int constw, unsigned int consth, t_world world, int reset)
{
	int 					*a_d = 0;
	size_t		size = constw * consth * sizeof(int);
 	cudaMalloc(&a_d, size);



	t_sphere				*spheres_d = NULL;
	t_plane					*planes_d = NULL;
	t_cylinder			*cylinders_d = NULL;
	t_cone				*cones_d = NULL;
	t_disk				*disks_d = NULL;
	t_torus					*torus_d = NULL;
	t_mobius				*mobius_d = NULL;
	t_cube				*cubes_d = NULL;
	t_triangle			*triangles_d = NULL;
	t_paraboloid			*paraboloids_d = NULL;
	t_hyperboloid		*hyperboloids_d = NULL;
	t_light					*lights_d = NULL;

	dim3			threads_per_block(32, 32);
	dim3			grid_size(constw / threads_per_block.x, consth / threads_per_block.y);

	// checkCUDAError("test4");
	// cudaMalloc((void**)&a_d, (int)constw * (int)consth * sizeof(int));
 	// cudaMemcpy(a_d, a_h, (int)constw * (int)consth * sizeof(int), cudaMemcpyHostToDevice);
	// checkCUDAError("before malloc objs");
	
	
	cudaMalloc(&spheres_d, sizeof(t_sphere) * world.spheres_len);
	cudaMalloc(&planes_d, sizeof(t_plane) * world.planes_len);
	
	cudaMalloc(&cylinders_d, sizeof(t_cylinder) * world.cylinders_len);
	cudaMalloc(&cubes_d, sizeof(t_cube) * world.cubes_len);
	cudaMalloc(&triangles_d, sizeof(t_triangle) * world.triangles_len);
	
	cudaMalloc(&torus_d, sizeof(t_torus) * world.torus_len);
	
	cudaMalloc(&mobius_d, sizeof(t_mobius) * world.mobius_len);
	cudaMalloc(&paraboloids_d, sizeof(t_paraboloid) * world.paraboloids_len);
	cudaMalloc(&hyperboloids_d, sizeof(t_hyperboloid) * world.hyperboloids_len);
	cudaMalloc(&cones_d, sizeof(t_cone) * world.cones_len);
	cudaMalloc(&disks_d, sizeof(t_disk) * world.disks_len);
	
	cudaMalloc(&lights_d, sizeof(t_light) * world.lights_len);
	
	// checkCUDAError("after malloc objs -- before memcpy objs");
	
	cudaMemcpy(spheres_d, world.spheres, sizeof(t_sphere) * world.spheres_len, cudaMemcpyHostToDevice);
	cudaMemcpy(planes_d, world.planes, sizeof(t_plane) * world.planes_len, cudaMemcpyHostToDevice);
	
	cudaMemcpy(cylinders_d, world.cylinders, sizeof(t_cylinder) * world.cylinders_len, cudaMemcpyHostToDevice);
	cudaMemcpy(cubes_d, world.cubes, sizeof(t_cube) * world.cubes_len, cudaMemcpyHostToDevice);
	cudaMemcpy(triangles_d, world.triangles, sizeof(t_triangle) * world.triangles_len, cudaMemcpyHostToDevice);
	
	cudaMemcpy(torus_d, world.torus, sizeof(t_torus) * world.torus_len, cudaMemcpyHostToDevice);
	
	cudaMemcpy(mobius_d, world.mobius, sizeof(t_mobius) * world.mobius_len, cudaMemcpyHostToDevice);
	cudaMemcpy(paraboloids_d, world.paraboloids, sizeof(t_paraboloid) * world.paraboloids_len, cudaMemcpyHostToDevice);
	cudaMemcpy(hyperboloids_d, world.hyperboloids, sizeof(t_hyperboloid) * world.hyperboloids_len, cudaMemcpyHostToDevice);
	cudaMemcpy(cones_d, world.cones, sizeof(t_cone) * world.cones_len, cudaMemcpyHostToDevice);
	cudaMemcpy(disks_d, world.disks, sizeof(t_disk) * world.disks_len, cudaMemcpyHostToDevice);
	
	cudaMemcpy(lights_d, world.lights, sizeof(t_light) * world.lights_len, cudaMemcpyHostToDevice);
	
	// checkCUDAError("after memcpy -- before world obj cpy");

	world.planes = planes_d;
	world.spheres = spheres_d;
	world.cylinders = cylinders_d;
	world.torus = torus_d;
	world.mobius = mobius_d;
	world.cubes = cubes_d;
	world.triangles = triangles_d;
	world.cones = cones_d;
	world.hyperboloids = hyperboloids_d;
	world.paraboloids = paraboloids_d;
	world.disks = disks_d;
	world.lights = lights_d;
	// cudaSetDevice(device);
	// cudaDeviceSetLimit(cudaLimitDevRuntimeSyncDepth, 0);
	// checkCUDAError("before RT");
	
	test <<< grid_size, threads_per_block >>> (a_d, constw, consth, world);
	
	// checkCUDAError("after RT");
	// cudaDeviceSynchronize();
	// checkCUDAError("end4");

	// checkCUDAError("before free");
	if(spheres_d != NULL)
		cudaFree(spheres_d);
	if(planes_d != NULL)
		cudaFree(planes_d);
	 if(cubes_d != NULL)
	 	cudaFree(cubes_d);
	 if(cylinders_d != NULL)
	 	cudaFree(cylinders_d);
	 if(cones_d != NULL)
	 	cudaFree(cones_d);
	 if(paraboloids_d != NULL)
	 	cudaFree(paraboloids_d);
	 if(hyperboloids_d != NULL)
	 	cudaFree(hyperboloids_d);
	 if(triangles_d != NULL)
	 	cudaFree(triangles_d);
	 if(disks_d != NULL)
	 	cudaFree(disks_d);
	if(torus_d != NULL)
		cudaFree(torus_d);
	 if(mobius_d != NULL)
	 	cudaFree(mobius_d);
	if(lights_d != NULL)
		cudaFree(lights_d);
	// checkCUDAError("after free");

	cudaMemcpy(a_h, a_d, size, cudaMemcpyDeviceToHost);

	if(a_d != NULL)
		cudaFree(a_d);
	// checkCUDAError("end");
	// checkCUDAError("end");
}


//
// int nDevices;
//
// cudaGetDeviceCount(&nDevices);
// for (int i = 0; i < nDevices; i++) {
// 	cudaDeviceProp prop;
// 	cudaGetDeviceProperties(&prop, i);
// 	printf("Device Number: %d\n", i);
// 	printf("  Device name: %s\n", prop.name);
// 	printf("  Major: %d\n", prop.major);
// 	printf("  Minor: %d\n", prop.minor);
// 	printf("  Memory Clock Rate (KHz): %d\n",
// 		   prop.memoryClockRate);
// 	printf("  Memory Bus Width (bits): %d\n",
// 		   prop.memoryBusWidth);
// 	printf("  Peak Memory Bandwidth (GB/s): %f\n\n",
// 		   2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6);
// }
