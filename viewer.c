#include "viewer.h"

void	viewer_fill(t_viewer *viewer, t_vec lookfrom, t_vec vup, t_vec lookat)
{
	viewer->lookat = lookat;
	viewer->lookfrom = lookfrom;
	viewer->vup = vup;
}
