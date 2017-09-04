#include <rt.h>

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
