#include "viewer.h"
#include "vector.h"

void	viewer_fill(t_viewer *viewer, t_vec vup, t_vec lookfrom, t_vec lookat, double hfov)
{
	viewer->lookat = lookat;
	viewer->lookfrom = lookfrom;
	viewer->vup = vup;
	viewer->hfov = hfov;
}

void	viewer_defaultFill(t_viewer *viewer, t_vec lookfrom, double hfov, t_vec orientation_vector)
{
	viewer->lookfrom = lookfrom;
	viewer->hfov = hfov;

	//by default mini rt assumes this
	vec_fillVec(&viewer->vup, 0, 1, 0);

	//since orientation vector = lookat - lookfrom
	vec_add(&viewer->lookat, &orientation_vector, &lookfrom);
}
