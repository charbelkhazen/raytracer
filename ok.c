#include "parser.h"
#include "light.h"
#include <stdio.h>
#include "vector.h"
#include "ambientlight.h"

int main()
{
	t_ambientLight ambient;
	char colstr[100];
	//char srcstr[100];

	printf("%d\n",pars_parseAmbient(&ambient,  "    1.0      256,255,255"));

	vec_toStr(colstr, &ambient.color, 1);

	//vec_toStr(srcstr, &light.src, 1);

	printf("ambient\ncolor:%s\nratio:%f\n", colstr, ambient.ratio);
}
