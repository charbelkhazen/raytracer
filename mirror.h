#ifndef MIRROR_H
#define MIRROR_H

typedef struct s_mirror
{
	int	onoff; //This has no purpose, its just a placeholder. I can replace it with roughness of material, But keep it like this, until code is well handled
}	t_mirror;

void	mirror_fillMirror(t_mirror *mirror, int onoff);
#endif
