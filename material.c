#include "material.h"
#include "matte.h"
#include "mirror.h"
#include "plastic.h"
#include "types.h"

void	mat_fillMatte(t_mat *mat, int onoff)
{
	mat->type = MATTE_TYPE;
	matte_fillMatte(&mat->as.matte, onoff);
}

void	mat_fillPlastic(t_mat *mat, int onoff)
{
	mat->type = PLASTIC_TYPE;
	plastic_fillPlastic(&mat->as.plastic, onoff);
}

void	mat_fillMirror(t_mat *mat, int onoff)
{
	mat->type = MIRROR_TYPE;
	mirror_fillMirror(&mat->as.mirror, onoff);
}
