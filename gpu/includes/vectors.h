/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:50:12 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:08:54 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
#ifndef CUDA_HOSTDEV
# ifdef __CUDA_ARCH__
# define CUDA_HOSTDEV __host__ __device__
# else
# define CUDA_HOSTDEV
# endif
#endif

typedef struct		s_vec2d
{
	double	x;
	double	y;
}					t_vec2d;

typedef struct		s_vec3d
{
	double	x;
	double	y;
	double	z;
}					t_vec3d;

CUDA_HOSTDEV t_vec3d					new_vector(double x, double y, double z);
CUDA_HOSTDEV t_vec3d					vector_add(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d					vector_substract(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d					vector_cross(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d				vector_scalar(t_vec3d vect1, double scalar);
CUDA_HOSTDEV double				vector_dot(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d				vector_calculate(t_vec3d	vect1, t_vec3d vect2);
CUDA_HOSTDEV double				vector_length(t_vec3d vect1);
CUDA_HOSTDEV t_vec3d				vector_normalize(t_vec3d vect1);

#endif
