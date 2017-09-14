#include "parse.h"
void 			parse_negative(int *negative, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
	{
		*negative = ft_atoi((char *)nb);
		if (*negative == 0 || *negative == 1)
			return (xmlFree(nb));
	}
	show_error_2("invalid negative value, should be == 0 or == 1. > data=",
		(const char *)nb);
	xmlFree(nb);
}

void			parse_reflection(double *reflection_coef, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
  {
		*reflection_coef = ft_atoi_double((const char *)nb);
    if (*reflection_coef >= 0 && *reflection_coef <= 1)
      return (xmlFree(nb));
    }
	show_error_2("invalid reflection value, should be >= 0 and <= 1. > data=",
    (const char *)nb);
	xmlFree(nb);
}

void			parse_refraction(double *refraction_coef, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
  {
		*refraction_coef = ft_atoi_double((const char *)nb);
    // if (*refraction_coef >= 1 && *refraction_coef <= 5)
      return (xmlFree(nb));
  }
	show_error_2("invalid refraction value, should be >= 1 and <= 5. > data=",
    (const char *)nb);
	xmlFree(nb);
}

void			parse_transparence(double *transparence_coef, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
  {
		*transparence_coef = ft_atoi_double((const char *)nb);
    if (*transparence_coef >= 0 && *transparence_coef <= 1)
      return (xmlFree(nb));
  }
	show_error_2("invalid transparence value, should be >= 0 and <= 1. > data=",
    (const char *)nb);
	xmlFree(nb);
}
