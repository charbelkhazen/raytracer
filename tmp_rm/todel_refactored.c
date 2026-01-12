void	obj_apply_material(t_obj *obj, t_hitRec *rec)
{
	if (obj->obj_matType == 'm')
		rec->material = *(t_mat *)obj->obj_mat;
	else
		exit(139);
}

static int	obj_hit_sphere(t_obj *obj, t_ray *ray, t_hitRec *rec, double tmin, double *tmax)
{
	t_sph	*sphere;

	sphere = (t_sph *)obj->obj_shape;
	if (!sph_hit(sphere, ray, tmin, *tmax, rec))
		return (0);
	*tmax = rec->t;
	obj_apply_material(obj, rec);
	return (1);
}

static int	obj_try_hit(t_obj *obj, t_ray *ray, t_hitRec *rec, double tmin, double *tmax)
{
	if (obj->obj_shapeType == 's')
		return (obj_hit_sphere(obj, ray, rec, tmin, tmax));
	return (0);
}

static int	univ_iterate_hits(t_ray *ray, t_univ *univ, t_hitRec *rec, double tmin, double *tmax)
{
	int	i;
	int	hit;

	i = 0;
	hit = 0;
	while (i < univ->len)
	{
		if (obj_try_hit(&univ->obj_lst[i], ray, rec, tmin, tmax))
			hit = 1;
		i++;
	}
	return (hit);
}

int	univ_hit(t_ray *ray, t_univ *univ, t_hitRec *rec)
{
	double	tmin;
	double	tmax;

	tmin = 0.001;
	tmax = 1e6;
	return (univ_iterate_hits(ray, univ, rec, tmin, &tmax));
}
