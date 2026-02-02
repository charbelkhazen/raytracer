app:
	cd minilibx-linux ; make; cd ..
	cc -Wall -Wextra -Werror *.c libft.a -Iminilibx-linux -Lminilibx-linux -lmlx -lX11 -lXext -lm

x:
	cd minilibx-linux ; make; cd ..
	cc *.c libft.a -Iminilibx-linux -Lminilibx-linux -lmlx -lX11 -lXext -lm
vec:
	cc vector.c stdlib.c -lm

test:
	cc ambientlight.c error.c image.c material.c parser.c render.c stdlib.c universe.c cylinder.c camera.c get_next_line_utils.c get_next_line.c light.c lambertphong.c matte.c plane.c ray.c shape.c todel.c vector.c viewer.c sphere.c object.c -lm
