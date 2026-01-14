#ifndef VIEWER_H
#define VIEWER_H
# include "vector.h"

typedef struct s_viewer
{
	t_vec	lookfrom;
	t_vec	lookat;
	t_vec	vup; //vector that defines x and y on plane orth. to look_at dir
}	t_viewer;

void	viewer_fill(t_viewer *viewer, t_vec lookfrom, t_vec vup, t_vec lookat);

#endif
