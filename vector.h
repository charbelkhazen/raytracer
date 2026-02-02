#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_s
{
	double	x;
	double	y;
	double	z;
}	t_vec;

void	vec_centerVec(t_vec *vec);

void	vec_fillVec(t_vec *vec, double x, double y, double z);

//vec1 - vec2
void	vec_subs(t_vec *result, t_vec *vec1, t_vec *vec2);

void	vec_add(t_vec *result, t_vec *vec1, t_vec *vec2);

void	vec_scale(t_vec *result, double factor, t_vec *vec);

double	vec_squaredLen(t_vec *v);

double	vec_vectorLen(t_vec *v);

void	vec_unitVector(t_vec *res, t_vec *v);

void	vec_cross(t_vec *result, t_vec *v1, t_vec *v2);

double	vec_dot(t_vec *v1, t_vec *v2);

/*string should be at least vec_strLen(t_vec, int) bytes*/
int	vec_strLen(t_vec *vector, int precision);
void	vec_toStr(char *string, t_vec *vector, int precision);

void	vec_componentWiseMultiplication(t_vec *result, t_vec *v1, t_vec *v2);

#endif
