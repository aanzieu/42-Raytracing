#include "../../includes/parse.h"

void	add_torus(t_torus **alst, t_torus *nw)
{
	t_torus *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = nw;
	}
}

void	parse_torus(t_world *world, xmlNodePtr cur)
{
	t_torus	*s;

	cur = cur->xmlChildrenNode;
	if (!(s = (t_torus*)ft_memalloc(sizeof(t_torus))))
		show_error("error malloc torus");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			parse_vec3d(&s->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
			parse_tra(&s->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius_small")))
			parse_radius(&s->radius_small, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius_big")))
			parse_radius(&s->radius_big, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&s->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&s->reflection_coef, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
			parse_refraction(&s->refraction_coef, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"transparence")))
			parse_reflection(&s->transparence_coef, cur);
		cur = cur->next;
	}
	add_mobius(&world->mobius_tmp, new_mobius(s, world->id++));
	free(s);
}
