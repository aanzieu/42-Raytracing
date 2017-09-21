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
  if ( cudaSuccess != err) {
    fprintf(stderr, "Cuda error: %s: %s.\n", msg, cudaGetErrorString( err) );
	system("pause");
    exit(EXIT_FAILURE);
  }
}

__global__ void test(int *a, unsigned int constw, unsigned int consth, t_world world)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int index = row * constw + col;
	int yy = world.aa * row + world.offsets.y_min;
	int xx = world.aa * col;
	a[index] = ray_tracer_gpu(world, xx, yy);
}

extern "C" void render_cuda(int *a_h, unsigned int constw, unsigned int consth, t_world world, int reset)
{
	int 					*a_d = 0;
	int 					*p;
	size_t				size = constw * consth * sizeof(int);

	dim3						threads_per_block(32, 32);
	dim3						grid_size(constw / threads_per_block.x, consth / threads_per_block.y);

	t_sphere				*spheres_d = NULL;
	t_plane					*planes_d = NULL;
	t_cylinder			*cylinders_d = NULL;
	t_cone					*cones_d = NULL;
	t_disk					*disks_d = NULL;
	t_torus					*torus_d = NULL;
	t_mobius				*mobius_d = NULL;
	t_cube					*cubes_d = NULL;
	t_h_cube				*h_cubes_d = NULL;
	t_triangle			*triangles_d = NULL;
	t_paraboloid		*paraboloids_d = NULL;
	t_hyperboloid		*hyperboloids_d = NULL;
	t_light					*lights_d = NULL;

	static int p_test[] = {
		151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140,
		36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120,
		234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
		88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
		134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133,
		230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161,
		1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130,
		116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
		124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227,
		47, 16, 58, 17, 182, 189, 28, 42, 23, 183, 170, 213, 119, 248, 152, 2, 44,
		154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98,
		108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34,
		242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
		239, 107, 49, 192, 214,  31, 181, 199, 106, 157, 184,  84, 204, 176, 115,
		121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72,
		243, 141, 128, 195, 78, 66, 215, 61, 156, 180
	};
	cudaMalloc(&p, sizeof(int) * 512);
	cudaMemcpy(p, p_test, sizeof(int) * 256, cudaMemcpyHostToDevice);
	cudaMemcpy((p + 256), p_test, sizeof(int) * 256, cudaMemcpyHostToDevice);
	world.p = p;

	cudaMalloc(&a_d, size);
	cudaMalloc(&spheres_d, sizeof(t_sphere) * world.spheres_len);
	cudaMalloc(&planes_d, sizeof(t_plane) * world.planes_len);
	cudaMalloc(&cylinders_d, sizeof(t_cylinder) * world.cylinders_len);
	cudaMalloc(&cubes_d, sizeof(t_cube) * world.cubes_len);
	cudaMalloc(&h_cubes_d, sizeof(t_h_cube) * world.h_cubes_len);
	cudaMalloc(&triangles_d, sizeof(t_triangle) * world.triangles_len);
	cudaMalloc(&torus_d, sizeof(t_torus) * world.torus_len);
	cudaMalloc(&mobius_d, sizeof(t_mobius) * world.mobius_len);
	cudaMalloc(&paraboloids_d, sizeof(t_paraboloid) * world.paraboloids_len);
	cudaMalloc(&hyperboloids_d, sizeof(t_hyperboloid) * world.hyperboloids_len);
	cudaMalloc(&cones_d, sizeof(t_cone) * world.cones_len);
	cudaMalloc(&disks_d, sizeof(t_disk) * world.disks_len);
	cudaMalloc(&lights_d, sizeof(t_light) * world.lights_len);

	cudaMemcpy(spheres_d, world.spheres, sizeof(t_sphere) * world.spheres_len, cudaMemcpyHostToDevice);
	cudaMemcpy(planes_d, world.planes, sizeof(t_plane) * world.planes_len, cudaMemcpyHostToDevice);
	cudaMemcpy(cylinders_d, world.cylinders, sizeof(t_cylinder) * world.cylinders_len, cudaMemcpyHostToDevice);
	cudaMemcpy(cubes_d, world.cubes, sizeof(t_cube) * world.cubes_len, cudaMemcpyHostToDevice);
	cudaMemcpy(h_cubes_d, world.h_cubes, sizeof(t_h_cube) * world.h_cubes_len, cudaMemcpyHostToDevice);
	cudaMemcpy(triangles_d, world.triangles, sizeof(t_triangle) * world.triangles_len, cudaMemcpyHostToDevice);
	cudaMemcpy(torus_d, world.torus, sizeof(t_torus) * world.torus_len, cudaMemcpyHostToDevice);
	cudaMemcpy(mobius_d, world.mobius, sizeof(t_mobius) * world.mobius_len, cudaMemcpyHostToDevice);
	cudaMemcpy(paraboloids_d, world.paraboloids, sizeof(t_paraboloid) * world.paraboloids_len, cudaMemcpyHostToDevice);
	cudaMemcpy(hyperboloids_d, world.hyperboloids, sizeof(t_hyperboloid) * world.hyperboloids_len, cudaMemcpyHostToDevice);
	cudaMemcpy(cones_d, world.cones, sizeof(t_cone) * world.cones_len, cudaMemcpyHostToDevice);
	cudaMemcpy(disks_d, world.disks, sizeof(t_disk) * world.disks_len, cudaMemcpyHostToDevice);
	cudaMemcpy(lights_d, world.lights, sizeof(t_light) * world.lights_len, cudaMemcpyHostToDevice);

	world.planes = planes_d;
	world.spheres = spheres_d;
	world.cylinders = cylinders_d;
	world.torus = torus_d;
	world.mobius = mobius_d;
	world.cubes = cubes_d;
	world.h_cubes = h_cubes_d;
	world.triangles = triangles_d;
	world.cones = cones_d;
	world.hyperboloids = hyperboloids_d;
	world.paraboloids = paraboloids_d;
	world.disks = disks_d;
	world.lights = lights_d;

	test <<< grid_size, threads_per_block >>> (a_d, constw, consth, world);
	printf("test2\n");
	cudaMemcpy(a_h, a_d, size, cudaMemcpyDeviceToHost);

	if (spheres_d != NULL)
		cudaFree(spheres_d);
	if (planes_d != NULL)
		cudaFree(planes_d);
	if (cubes_d != NULL)
		cudaFree(cubes_d);
	if (h_cubes_d != NULL)
		cudaFree(h_cubes_d);
	if (cylinders_d != NULL)
		cudaFree(cylinders_d);
	if (cones_d != NULL)
		cudaFree(cones_d);
	if (paraboloids_d != NULL)
		cudaFree(paraboloids_d);
	if (hyperboloids_d != NULL)
		cudaFree(hyperboloids_d);
	if (triangles_d != NULL)
		cudaFree(triangles_d);
	if (disks_d != NULL)
		cudaFree(disks_d);
	if (torus_d != NULL)
		cudaFree(torus_d);
	if (mobius_d != NULL)
		cudaFree(mobius_d);
	if (lights_d != NULL)
		cudaFree(lights_d);
	if (a_d != NULL)
		cudaFree(a_d);
	if (p != NULL)
		cudaFree(p);
	printf("test3\n");
}
