#include "image.h"

void	img_fill(t_img *img, int img_width, double img_ratio)
{
	img->img_width = img_width;
	img->img_ratio = img_ratio;
	img->img_height = (int)((double)img_width / img_ratio);
	if (img->img_height < 1)
		img->img_height = 1;
}

