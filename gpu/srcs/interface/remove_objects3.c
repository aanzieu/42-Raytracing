#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "header/nuklear.h"
#include "header/gui.h"


void			remove_triangle(t_triangle **s, t_intersection *i)
{
	t_triangle	*current;
	t_triangle	*last;
	t_triangle	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current->id == i->id)
		{
			if (current == *s)
				*s = current->next;
			else
				last->next = current->next;
			tmp = current;
			current = current->next;
			free(tmp);
		}
		else
		{
			last = current;
			current = current->next;
		}
	}
}
