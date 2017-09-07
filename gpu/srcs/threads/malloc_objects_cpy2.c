
#include <rt.h>

t_torus			*copy_torus(t_torus *obj)
{
	t_torus 	*news;

	if (obj)
	{
		if (!(news = (t_torus *)malloc(sizeof(t_torus))))
			ft_putendl_fd("error : can't malloc copy thread torus\n", 1);
		news->radius_small = obj->radius_small;
		news->radius_big = obj->radius_big;
		news->pos = obj->pos;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_torus(obj->next);
		return (news);
	}
	return (NULL);
}

t_mobius		*copy_mobius(t_mobius *obj)
{
	t_mobius *news;

	if (obj)
	{
		if (!(news = (t_mobius *)malloc(sizeof(t_mobius))))
			ft_putendl_fd("error : can't malloc copy thread mobius\n", 1);
		news->radius = obj->radius;
		news->pos = obj->pos;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_mobius(obj->next);
		return (news);
	}
	return (NULL);
}

t_disk		*copy_disk(t_disk *obj)
{
	t_disk 	*news;

	if (obj)
	{
		if (!(news = (t_disk *)malloc(sizeof(t_disk))))
			ft_putendl_fd("error : can't malloc copy thread disk\n", 1);
		news->radius = obj->radius;
		news->radius_squared = obj->radius_squared;
		news->pos = obj->pos;
		news->up = obj->up;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_disk(obj->next);
		return (news);
	}
	return (NULL);
}

t_cube		*copy_cube(t_cube *obj)
{
	t_cube 	*news;

	if (obj)
	{
		if (!(news = (t_cube *)malloc(sizeof(t_cube))))
			ft_putendl_fd("error : can't malloc copy thread cube\n", 1);
		news->min = obj->min;
		news->max = obj->max;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_cube(obj->next);
		return (news);
	}
	return (NULL);
}

t_hyperboloid		*copy_hyperboloid(t_hyperboloid *obj)
{
	t_hyperboloid *news;

	if (obj)
	{
		if (!(news = (t_hyperboloid *)malloc(sizeof(t_hyperboloid))))
			ft_putendl_fd("error : can't malloc copy thread hyperboloid\n", 1);
		news->top = obj->top;
		news->normal = obj->normal;
		news->radius = obj->radius;
		news->maxm = obj->maxm;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_hyperboloid(obj->next);
		return (news);
	}
	return (NULL);
}
