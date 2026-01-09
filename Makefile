app:
	cd minilibx-linux ; make; cd ..
	cc -Wall -Wextra -Werror *.c libft.a -Iminilibx-linux -Lminilibx-linux -lmlx -lX11 -lXext -lm

x:
	cd minilibx-linux ; make; cd ..
	cc *.c libft.a -Iminilibx-linux -Lminilibx-linux -lmlx -lX11 -lXext -lm
vec:
	cc vector.c stdlib.c -lm
	
