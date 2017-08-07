
#include "../../includes/rt.h"

static unsigned int	count_hyperboloids(t_hyperboloid *hyperboloids)
{
	t_hyperboloid *h;
	unsigned int size;

	size = 0;
	h = hyperboloids;
	while (h)
	{
		size++;
		h = h->next;
	}
	return (size);
}

void			load_hyperboloids(t_hyperboloid **hyperboloids, t_hyperboloid *hyperboloids_tmp, int *hyperboloids_len)
{
	unsigned int i;
	t_hyperboloid *tmp;

	i = 0;
	*hyperboloids_len = count_hyperboloids(hyperboloids_tmp);
	*hyperboloids = (t_hyperboloid*)malloc(sizeof(t_hyperboloid) * *hyperboloids_len);
	tmp = hyperboloids_tmp;
	while (tmp)
	{
		(*hyperboloids)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
