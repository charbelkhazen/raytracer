int	vec_centerVec(vec_t *v)
{
	v->x = 0;
	v->y = 0;
	v ->z = 0;
	return (0);
}

int	vec_subs(vec_t *r, vec_t *v1, vec_t *v2)
{
	r->x = v1->x - v2->x;
	r->y = v1->y - v2->y;
	r->z = v1->z - v2->z;
	return (0);
}

int	vec_add(vec_t *r, vec_t *v1, vec_t *v2)
{
	r->x = v1->x + v2->x;
	r->y = v1->y + v2->y;
	r->z = v1->z + v2->z;
	return (0);
}

int	vec_scale(vec_t *r, double f, vec_t *v)
{
	r->x = f * v->x;
	r->y = f * v->y;
	r->z = f * v->z;
	return (0);
}

int	vec_toStr(vect_t *v)
{
	
}
