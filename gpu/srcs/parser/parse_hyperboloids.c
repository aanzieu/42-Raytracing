
#include "../../../gpu/includes/parse.h"

static void				get_hyperboloid_next(t_world *world, char **tmp,
		int i, t_hyperboloid *hyper)
{
	if (ft_strnequ(tmp[i], "<top>", ft_strlen("<top>")))
		parse_point(&hyper->top, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&hyper->normal, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		hyper->radius = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<height>", ft_strlen("<height>")))
		hyper->maxm = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&hyper->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<reflexion>", ft_strlen("<reflexion>")))
		parse_reflexion(&hyper->reflexion_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<refraxion>", ft_strlen("<refraxion>")))
		parse_refraxion(&hyper->refraxion_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&hyper->top, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&hyper->normal, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<chess>", ft_strlen("<chess>")))
		parse_color(&hyper->chess, tmp, world->line);
}

void					parse_hyperboloid(t_world *world, t_list *lst)
{
	t_hyperboloid *hyper;
	char	**tmp;
	int		i;

	if (!(hyper = (t_hyperboloid *)ft_memalloc(sizeof(t_hyperboloid))))
		ft_putendl_fd("error malloc Paraboloid", 1);
	hyper->chess.r = -1;
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		hyper->refraxion_coef = 0;
		while (tmp[++i] != NULL)
			get_hyperboloid_next(world, tmp, i, hyper);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_hyperboloid(&world->hyperboloids_tmp, new_hyperboloid(hyper, world->obj_id++));
	free(hyper);
}
