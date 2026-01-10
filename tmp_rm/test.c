#include "universe.h"
#define	NUM_OBJ 100
#include "object.h"

#include <stdio.h>
int main()
{
	t_univ	univ;
	t_obj	obj_lst[NUM_OBJ];
	t_obj	obj1;
	t_obj	obj2;
	
	univ_init(&univ, obj_lst, NUM_OBJ);
	univ_push(&univ, obj1);
	univ_push(&univ, obj2);
	printf("%d\n", univ.len);
}
