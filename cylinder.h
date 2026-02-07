#ifndef CYLINDER_H
# define CYLINDER_H

#include "intersection.h"
#include "ray.h"
#include "interval.h"

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	normalized_axis;
	t_vec	color;
	double	diameter;
	double 	radius;
	double	height;
}	t_cylinder;

void	cyl_fillCyl(t_cylinder *cyl, t_vec center, t_vec normalized_axis, t_vec color, double diameter, double height);

//returns bool AND if hit fills hitRec
//Refer to my note on line cylinder intersection to understand logic
int	cyl_hit(t_cylinder *cyl, t_ray *ray, t_interval *time_interval, t_hitRec *rec);

#endif
