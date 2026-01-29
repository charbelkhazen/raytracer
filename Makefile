app:
	cd minilibx-linux ; make; cd ..
	cc -Wall -Wextra -Werror *.c libft.a -Iminilibx-linux -Lminilibx-linux -lmlx -lX11 -lXext -lm

x:
	cd minilibx-linux ; make; cd ..
	cc *.c libft.a -Iminilibx-linux -Lminilibx-linux -lmlx -lX11 -lXext -lm
vec:
	cc vector.c stdlib.c -lm

test:
	cc parser.c viewer.c shape.c object.c image.c vector.c stdlib.c material.c  matte.c sphere.c ray.c camera.c get_next_line.c get_next_line_utils.c -lm lambertphong.c light.c ambientlight.c  universe.c testparse.c 

