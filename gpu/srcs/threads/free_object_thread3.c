
#include "../../includes/rt.h"
#include "../../includes/parse.h"

void		thread_free_and_add_paraboloid(t_paraboloid **p, t_paraboloid **p_tmp, int *len, int id)
{
	t_paraboloid	*new;

	if(*p != NULL)
	{
		free(*p);
		*len = 0;
		*p = NULL;
	}
	if (!(new = (t_paraboloid*)ft_memalloc(sizeof(t_paraboloid))))
		show_error("error malloc sphere");
	init_paraboloid_add(new);
	*len = 0;
	*p = NULL;
	add_paraboloid(p_tmp, new_paraboloid(new, id++));
	free(new);
	load_paraboloids(p, *p_tmp, len);
}

void		thread_free_and_add_triangle(t_triangle **t, t_triangle **t_tmp, int *len, int id)
{
	t_triangle	*new;

	if(*t != NULL)
	{
		free(*t);
		*len = 0;
		*t = NULL;
	}
	if (!(new = (t_triangle*)ft_memalloc(sizeof(t_triangle))))
		show_error("error malloc sphere");
	init_triangle_add(new);
	*len = 0;
	*t = NULL;
	add_triangle(t_tmp, new_triangle(new, id++));
	free(new);
	load_triangles(t, *t_tmp, len);
}
