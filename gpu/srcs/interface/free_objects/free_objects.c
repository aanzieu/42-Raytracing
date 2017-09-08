
#include "../../../includes/rt.h"

void		free_plan(t_plane **p_tmp, t_plane **p, int *len)
{
    t_plane	*next;

  
   while (*p_tmp)
   {
       next = (*p_tmp)->next;
       free(*p_tmp);
       (*p_tmp) = next;
   }
   if(*p != NULL)
   {
       free(*p);
       *len = 0;
       *p = NULL;
   }
   *p = 0;
   *p = NULL;
   printf("free lights\n");
}

void		free_sphere(t_sphere **s_tmp, t_sphere **s, int *len)
{
    t_sphere	*next;

    printf("je rentre dans sphers\n");
    while (*s_tmp)
    {
        next = (*s_tmp)->next;
        free(*s_tmp);
        (*s_tmp) = next;
    }
    if(*s != NULL)
    {
        free(*s);
        *len = 0;
        *s = NULL;
    }
    *s = 0;
    *s = NULL;
}

void		free_cone(t_cone **c_tmp, t_cone **c, int *len)
{
    t_cone	*next;

    printf("je rentre dans sphers\n");
    while (*c_tmp)
    {
        next = (*c_tmp)->next;
        free(*c_tmp);
        (*c_tmp) = next;
    }
    if(*c != NULL)
    {
        free(*c);
        *len = 0;
        *c = NULL;
    }
    *c = 0;
    *c = NULL;
}

void		free_cy(t_cylinder **c_tmp, t_cylinder **c, int *len)
{
    t_cylinder	*next;

    while (*c_tmp)
    {
        next = (*c_tmp)->next;
        free(*c_tmp);
        (*c_tmp) = next;
    }
    if(*c != NULL)
    {
        free(*c);
        *len = 0;
        *c = NULL;
    }
    *c = 0;
    *c = NULL;
    
}

void		free_light(t_light **l_tmp, t_light **l, int *len)
{
    t_light	*next;

    printf("je rentre dans lights\n");
   //  if(*l == NULL)
   // 	 return;
    while (*l_tmp)
    {
        next = (*l_tmp)->next;
        free(*l_tmp);
        (*l_tmp) = next;
    }
    if(*l != NULL)
    {
        free(*l);
        *len = 0;
        *l = NULL;
    }
    *len = 0;
    *l = NULL;
    printf("free lights\n");
    
}