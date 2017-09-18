#include "parse.h"

void	add_h_cube(t_h_cube **alst, t_h_cube *nw)
{
	t_h_cube *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = nw;
	}
}

void 	handle_input_h_cube(t_h_cube *c, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
		parse_vec3d(&c->pos, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		parse_color(&c->color, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
		parse_color(&c->chess, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		parse_reflection(&c->reflection_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		parse_refraction(&c->refraction_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"transparence")))
		parse_transparence(&c->transparence_coef, cur);
}

void	parse_h_cube(t_world *world, xmlNodePtr cur)
{
	t_h_cube *c;

	cur = cur->xmlChildrenNode;
	if (!(c = (t_h_cube *)ft_memalloc(sizeof(t_h_cube))))
		show_error("error malloc h_cube");
	c->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		handle_input_h_cube(c, cur);
		cur = cur->next;
	}
	add_h_cube(&world->h_cubes_tmp, new_h_cube(c, world->id++));
	free(c);
}
