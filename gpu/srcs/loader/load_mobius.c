
#include "../../includes/rt.h"

static unsigned int			count_mobius(t_mobius *mobius)
{
	t_mobius *s;
	unsigned int size;

	size = 0;
	s = mobius;
	while (s)
	{
		size++;
		s = s->next;
	}
	return (size);
}

void			load_mobius(t_mobius **mobius, t_mobius *mobius_tmp, int *mobius_len)
{
	unsigned int i;
	t_mobius *tmp;

	i = 0;
	*mobius_len = count_mobius(mobius_tmp);
	*mobius = (t_mobius*)malloc(sizeof(t_mobius) * *mobius_len);
	tmp = mobius_tmp;
	while (tmp)
	{
		(*mobius)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
