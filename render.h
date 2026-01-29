#ifndef RENDER_H
#define RENDER_H

# include "ui.h"
# include "scene.h"

void	render_logicToMlx(ui_mlxParams_t *params, t_scene *scene);

//sould be in render!!!
//temporary function - needs modif
void	cam_rayColor(t_vec *color, t_ray *ray, t_univ *univ, t_light *light); // hit record should  be part of ray? 

#endif
