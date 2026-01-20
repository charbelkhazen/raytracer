#include "parser.h"
#include "light.h"
#include <stdio.h>
#include "vector.h"
#include "ambientlight.h"
# include "viewer.h"

int main()
{
	t_viewer view;
	char strlookfrom[100];
	char strlookat[100];
	char strorientation[100];
	char strvup[100];

	printf("%d\n",pars_parseCamera(&view,  "-50.0,0,20 0,0,1 70"));

	vec_toStr(strlookfrom, &view.lookfrom, 1);
	vec_toStr(strlookat, &view.lookat, 1);
	//vec_toStr(strorientation, &view.strorientation, 1);
	vec_toStr(strvup, &view.vup, 1);


	printf("ambient\nlookfom:%s\nlookat:%s\nvup:%s\nhfov:%f\n", strlookfrom, strlookat, strvup, view.hfov);
}
