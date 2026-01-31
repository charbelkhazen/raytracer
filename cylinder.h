#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	normalized_axis;
	double	diameter;
	double	height;
}	t_cylinder;

void	cyl_fillCyl(t_cylinder *cyl, t_vec center, t_vec normalized_axis, double diameter, double height);

//returns bool AND if hit fills hitRec
int	sph_hit(t_cylinder *cyl, t_ray *ray, double t_min, double t_max, t_hitRec *rec);

#endif
