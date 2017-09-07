
#include <rt.h>

t_paraboloid		*copy_paraboloid(t_paraboloid *obj)
{
	t_paraboloid	*news;

	if (obj)
	{
		if (!(news = (t_paraboloid *)malloc(sizeof(t_paraboloid))))
			ft_putendl_fd("error : can't malloc copy thread paraboloid\n", 1);
		news->normal = obj->normal;
		news->top = obj->top;
		news->distance = obj->distance;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_paraboloid(obj->next);
		return (news);
	}
	return (NULL);
}

t_triangle		*copy_triangle(t_triangle *obj)
{
	t_triangle 	*news;

	if (obj)
	{
		if (!(news = (t_triangle *)malloc(sizeof(t_triangle))))
			ft_putendl_fd("error : can't malloc copy thread triangle\n", 1);
		news->pos = obj->pos;
		news->up = obj->up;
		news->v1 = obj->v1;
		news->v2 = obj->v2;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_triangle(obj->next);
		return (news);
	}
	return (NULL);
}
