#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H
# include "vector.h"

typedef struct s_ambientLight
{
	double ratio;
	t_vec	color;
}	t_ambientLight;

void	al_fill(t_ambientLight *amb_light, double ratio, t_vec color);

#endif
