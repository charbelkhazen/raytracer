#ifndef VIEWER_H
# define VIEWER_H
# include "vector.h"

typedef struct s_viewer
{
	t_vec	lookfrom;
	t_vec	lookat;
	t_vec	vup; //vector that defines x and y on plane orth. to lookat dir
	double	hfov;
}	t_viewer;

void	viewer_fill(t_viewer *viewer, t_vec vup, t_vec lookfrom, t_vec lookat, double hfov);

//fill viewer under default parameters
// TAKES ORIENTATION VECTOR AS PARAMETER AND FINDS LOOKAT FROM IT
void	viewer_defaultFill(t_viewer *viewer, t_vec lookfrom, double hfov, t_vec orientation_vector);
#endif
