#include <math.h>
#include <stdlib.h>
#include "sphere.h"
#include "ray.h"
#include "object.h"


void sph_create(t_sphere sphere, t_vec center, double radius);




int sphere_hit(const t_ray *ray, double t_min, double t_max, t_hitRec *rec)
{
    t_sphere *sphere = (t_sphere *)obj;
    t_vec oc;
    double a;
    double h;
    double c;
    double discriminant;
    double sqrtd;
    double root;

    oc = v_sub(sphere->center, ray->orig);
    a = v_len2(ray->dir);
    h = v_dot(ray->dir, oc);
    c = v_len2(oc) - sphere->radius * sphere->radius;

    discriminant = h * h - a * c;
    if (discriminant < 0)
        return (0);

    sqrtd = sqrt(discriminant);

    /* nearest root */
    root = (h - sqrtd) / a;
    if (root <= t_min || root >= t_max)
    {
        root = (h + sqrtd) / a;
        if (root <= t_min || root >= t_max)
            return (0);
    }

    rec->t = root;
    rec->p = ray_at(ray, rec->t);
    rec->normal = v_div(v_sub(rec->p, sphere->center), sphere->radius);

    return (1);
}
