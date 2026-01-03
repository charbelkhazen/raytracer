#include "stdlib.h"
#include <math.h>
#include "vector.h"
#include <stdlib.h>

void	vec_centerVec(t_vec *v)
{
	v->x = 0;
	v->y = 0;
	v ->z = 0;
}

void	vec_subs(t_vec *r, t_vec *v1, t_vec *v2)
{
	r->x = v1->x - v2->x;
	r->y = v1->y - v2->y;
	r->z = v1->z - v2->z;
}

void	vec_add(t_vec *r, t_vec *v1, t_vec *v2)
{
	r->x = v1->x + v2->x;
	r->y = v1->y + v2->y;
	r->z = v1->z + v2->z;
}

void	vec_scale(t_vec *r, double f, t_vec *v)
{
	r->x = f * v->x;
	r->y = f * v->y;
	r->z = f * v->z;
}

double	vec_vectorLen(t_vec *v)
{
	return (sqrt(std_pow(v->x, 2) + std_pow(v->y, 2) + std_pow(v->z, 2)));
}

void	vec_unitVector(t_vec *res, t_vec *v)
{
	vec_scale(res, 1 / vec_vectorLen(v), v); 
}

int	vec_strLen(t_vec *v, int p)
{
	return (std_sizeArrayDouble(v->x, p) + std_sizeArrayDouble(v->y, p) + std_sizeArrayDouble(v->z, p));
}

void	vec_toStr(char *str, t_vec *v, int p)
{	
	std_dtoa(str, v->x, p);
	std_fillThenNull(str + std_strlen(str), ' ');
	std_dtoa(str + std_strlen(str), v->y, p);
	std_fillThenNull(str + std_strlen(str), ' ');
	std_dtoa(str + std_strlen(str), v->z, p);
}

//void	vec_unitVec(t_vec *result, t_vec *vec);

#include <stdio.h>
int main()
{
	t_vec v;
	v.x = 12.12;
	v.y = 12.13;
	v.z = 12.12;
	char str[vec_strLen(&v, 2)];
	vec_toStr(str, &v, 2);
	printf("str:%s\n", str);
	t_vec v2;
	vec_centerVec(&v2);
	vec_toStr(str, &v2, 2);
	printf("str:%s\n", str);

}
