#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

void			remove_torus(t_torus **s, t_intersection *i)
{
	t_torus	*current;
	t_torus	*last;
	t_torus	*tmp;

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

void			remove_mobius(t_mobius **s, t_intersection *i)
{
	t_mobius	*current;
	t_mobius	*last;
	t_mobius	*tmp;

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

void			remove_disk(t_disk **s, t_intersection *i)
{
	t_disk	*current;
	t_disk	*last;
	t_disk	*tmp;

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

void			remove_cube(t_cube **s, t_intersection *i)
{
	t_cube	*current;
	t_cube	*last;
	t_cube	*tmp;

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

void			remove_hyperboloid(t_hyperboloid **s, t_intersection *i)
{
	t_hyperboloid	*current;
	t_hyperboloid	*last;
	t_hyperboloid	*tmp;

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
