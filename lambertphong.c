# include "ray.h"
# include "universe.h"
# include "intersection.h"

int	lp_attenuationFactor(t_ray ray_to_light, t_univ univ)
{
	t_hitRec	rec;

	if (univ_hit(&ray_to_light, &univ, &rec))
		return (1);
	return (0);
}
