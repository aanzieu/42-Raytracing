
#include <rt.h>

static unsigned int			count_torus(t_torus *torus)
{
	t_torus *t;
	unsigned int size;

	size = 0;
	t = torus;
	while (t)
	{
		size++;
		t = t->next;
	}
	return (size);
}

void		            	load_torus(t_torus **torus, t_torus *torus_tmp, int *torus_len)
{
	unsigned int i;
	t_torus *tmp;

	i = 0;
	*torus_len = count_torus(torus_tmp);
	*torus = (t_torus*)malloc(sizeof(t_torus) * *torus_len);
	tmp = torus_tmp;
	while (tmp)
	{
		(*torus)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
