#ifndef RENDER_H
#define RENDER_H

# include "ui.h"
# include "scene.h"

# define MAX_RECURSION_DEPTH 5

//!important : it fills fills the pixel buffer according to the logic - and sets a default recursion depth
void	render_logicToMlx(ui_mlxParams_t *params, t_scene *scene);

void	render_rayColor(t_vec *color, t_ray *ray, t_scene *scene, int recursion_depth);
#endif
