#include "../../includes/rt.h"

t_cube	*new_cube(t_cube *nw, int id)
{
	t_cube	*t;

	if (!(t = (t_cube *)ft_memalloc(sizeof(t_cube))))
		ft_putendl_fd("Erroc Malloc on cube", 1);
	t->pos = nw->pos;
	t->up = nw->up;
	t->color = nw->color;
	t->chess = nw->chess;
	t->id = id;
	t->reflection_coef = nw->reflection_coef;
	t->refraction_coef = nw->refraction_coef;
	t->transparence_coef = nw->transparence_coef;
	t->next = NULL;
	return (t);
}
