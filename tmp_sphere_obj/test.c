#include <stdio.h>
#include "sphere.h"
#include "vector.h"

int main()
{
	t_vec	center;
	t_sph	sphere;

	vec_fillVec(&center, 1, 1, 1);
	sph_fillSph(&sphere, center, 2);
}
