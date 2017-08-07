
#include <parse.h>

static void	parse_torus_next(t_world *world, char **tmp, int i, t_torus *t)
{
	if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		t->radius = ft_atoi_double((tmp[i + 1]));
	else if (ft_strnequ(tmp[i], "<radius2>", ft_strlen("<radius2>")))
		t->radius2 = ft_atoi_double((tmp[i + 1]));
	else if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&t->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&t->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&t->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<reflection>", ft_strlen("<reflection>")))
		parse_reflection(&t->reflection_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<refraction>", ft_strlen("<refraction>")))
		parse_refraction(&t->refraction_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<chess>", ft_strlen("<chess>")))
		parse_color(&t->chess, tmp, world->line);
}

void		parse_torus(t_world *world, t_list *lst)
{
	t_torus	*t;
	char		**tmp;
	int			i;

	if (!(t = (t_torus *)ft_memalloc(sizeof(t_torus))))
		ft_putendl_fd("Error Malloc torus", 1);
		t->chess = (t_color){-1, -1, -1};
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			parse_torus_next(world, tmp, i, t);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_torus(&world->torus_tmp, new_torus(t, world->id++));
	free(t);
}
