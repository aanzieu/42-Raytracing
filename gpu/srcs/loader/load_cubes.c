#include <rt.h>

static unsigned int			count_cube(t_cube *cube)
{
	t_cube *t;
	unsigned int size;

	size = 0;
	t = cube;
	while (t)
	{
		size++;
		t = t->next;
	}
	return (size);
}

void                    load_cubes(t_cube **cubes,
    t_cube *cubes_tmp, int *cubes_len)
{
	unsigned int i;
	t_cube *tmp;

	i = 0;
	*cubes_len = count_cube(cubes_tmp);
	*cubes = (t_cube *)malloc(sizeof(t_cube) * *cubes_len);
	tmp = cubes_tmp;
	while (tmp)
	{
		(*cubes)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
