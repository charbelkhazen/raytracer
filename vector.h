#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_s
{
	double	x;
	double	y;
	double	z;
}	vec_t;

int	vec_centerVec(vec_t *vec);

int	vec_subs(vec_t *result, vec_t *vec1, vec_t *vec2);

int	vec_add(vec_t *result, vec_t *vec1, vec_t *vec2);

int	vec_scale(vec_t *result, double factor, vec_t *vec);

int	vec_toStr(vect_t *vector);

#endif
