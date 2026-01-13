#include "ambientlight.h"

void	al_fill(t_ambientLight *amb_light, double ratio, t_vec color)
{
	amb_light->ratio = ratio;
	amb_light->color = color;
}
