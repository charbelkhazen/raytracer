#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	normalized_axis;
	double	diameter;
	double	height;
}	t_cylinder;
	
#endif
