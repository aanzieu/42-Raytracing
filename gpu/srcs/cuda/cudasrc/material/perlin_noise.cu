#include <cuda.h>
#include <float.h>

extern "C" {
  #include "../../../../includes/vectors.h"
  #include "../../../../includes/rt.h"
  #include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ static double fade(double t)
{
   return (t * t * t * (t * (t * 6 - 15) + 10));
}

__host__ __device__ static double lerp(double t, double a, double b)
{
   return (a + t * (b - a));
}

__host__ __device__ static double grad(int hash, double x, double y, double z)
{
   int h = hash & 15;
   double u = h < 8 || h == 12 || h == 13 ? x : y;
	 double v = h < 4 || h == 12 || h == 13 ? y : z;
   return (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}

__host__ __device__ double apply_noise(t_world world, double x, double y,
	      double z)
{
   int X = (int)floor(x) & 255;
	 int Y = (int)floor(y) & 255;
	 int Z = (int)floor(z) & 255;
   x -= floor(x);
   y -= floor(y);
   z -= floor(z);
	 double u = fade(x);
	 double v = fade(y);
	 double w = fade(z);
	 int A = world.p[X] + Y;
	 int AA = world.p[A] + Z;
	 int AB = world.p[A + 1] + Z;
	 int B = world.p[X + 1] + Y;
	 int BA = world.p[B] + Z;
	 int BB = world.p[B + 1] + Z;
	 return (lerp(w, lerp(v, lerp(u, grad(world.p[AA], x, y, z),
			       grad(world.p[BA], x - 1, y, z)),
						 	lerp(u, grad(world.p[AB], x, y - 1, z),
			    	 		grad(world.p[BB], x - 1, y - 1, z))),
						 			lerp(v, lerp(u, grad(world.p[AA + 1], x, y, z - 1),
						 				grad(world.p[BA + 1], x - 1, y, z - 1)),
			               	lerp(u, grad(world.p[AB + 1], x, y - 1, z - 1),
			              		grad(world.p[BB + 1], x - 1, y - 1, z - 1)))));
}

__host__ __device__ t_vec3d normal_perturbation(t_world world, t_vec3d normal,
				t_vec3d intersection_pos, t_perlin perlin)
{
   t_vec3d noise;
	 t_vec3d normal_pert;
	 double x, y, z;
	//  double scale = 0.7;
	//  double amount = 2;

   x = intersection_pos.x / perlin.scale;
   y = intersection_pos.y / perlin.scale;
   z = intersection_pos.z / perlin.scale;
   noise.x = (float)(apply_noise(world, x, y, z));
   noise.y = (float)(apply_noise(world, y, z, x));
   noise.z = (float)(apply_noise(world, z, x, y));
	 normal_pert = vector_normalize(vector_add(normal,
		 	vector_scalar(noise, perlin.amount)));
   return (normal_pert);
}
