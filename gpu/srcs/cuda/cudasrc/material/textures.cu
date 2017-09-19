#include <cuda.h>
#include <float.h>

extern "C" {
  #include "../../../../includes/vectors.h"
  #include "../../../../includes/rt.h"
  #include "../../cudaheader/gpu_rt.h"
}

// __host__ __device__ t_color wood(t_world world, t_vec3d point, t_perlin perlin)
// {
//    double x = point.x * perlin.scale;
//    double y = point.y * perlin.scale;
//    double z = point.z * perlin.scale;
//
//    double grain = apply_noise(world, x, y, z) * 5;
//    grain = grain - (int)grain;
// 	 t_color color2, wood1, wood2;
// 	 wood1 = (t_color){155 / 255, 93 / 255, 73 / 255};
// 	 wood2 = (t_color){238 / 255, 170 / 255, 117 / 255};
// 	 color2 = color_add(color_scalar(wood1, grain), color_scalar(wood2, (1.0f - grain)));
//    return (color2);
// }
