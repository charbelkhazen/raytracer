#include "parser.h"
#include "light.h"
#include <stdio.h>
#include "vector.h"

int main()
{
	t_light light;
	char colstr[100];
	char srcstr[100];

	printf("%d\n",pars_parseLight(&light,  "-40.0 ,50.0,0.0 0.6 10,          0.9,255"));

	vec_toStr(colstr, &light.color, 1);
	vec_toStr(srcstr, &light.src, 1);
	printf("light coord:\n,color:%s\nsrc:%s\nbright:%f\n", colstr, srcstr, light.bright);
}
