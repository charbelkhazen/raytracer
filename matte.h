#ifndef MATTE_H
#define MATTE_H

typedef struct s_matte
{
	int	onoff; //This has no purpose, its just a placeholder. I can replace it with roughness of material, But keep it like this, until code is well handled
}	t_matte;

void	matte_fillMatte(t_matte *matte, int onoff);
#endif
