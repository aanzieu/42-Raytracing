#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void	init_triangle_add(t_triangle *t)
{
	t->id = 0;
	t->pos = new_vector(0, 0 , 0);
	t->v1 = new_vector(0, 1 , 1);
	t->v2 = new_vector(1, 1 , 0);
	t->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	t->chess = (t_color){-1, -1, -1};
	t->reflection_coef = 0;
	t->refraction_coef = 0;
	t->transparence_coef = 0;
	t->next = NULL;
}

static unsigned int	count_triangle(t_triangle *triangle)
{
	t_triangle		*t;
	unsigned int	size;

	size = 0;
	t = triangle;
	while (t)
	{
		size++;
		t = t->next;
	}
	return (size);
}

void 					load_triangles(t_triangle **triangles,
    t_triangle *triangles_tmp, int *triangles_len)
{
	unsigned int	i;
	t_triangle		*tmp;

	i = 0;
	*triangles_len = count_triangle(triangles_tmp);
	*triangles = (t_triangle *)malloc(sizeof(t_triangle) * *triangles_len);
	tmp = triangles_tmp;
	while (tmp)
	{
		(*triangles)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
