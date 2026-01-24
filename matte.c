#include "matte.h"
#include "material.h"

void	matte_fillMatte(t_matte *matte, int onoff)
{
	matte->type = onoff;
}
