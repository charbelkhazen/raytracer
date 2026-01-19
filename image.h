#ifndef IMAGE_H
# define IMAGE_H

typedef	struct	s_img
{
	int	img_width;
	int	img_height;
	double	img_ratio;
}	t_img;

void	img_fill(t_img *img, int img_width, double img_ratio);

#endif
