#include "universe.h"
#define	NUM_OBJ 100
int main()
{
	t_univ	univ;
	t_obj	obj_lst[NUM_OBJ];

	univ_init(&univ, obj_lst, NUM_OBJ);
}
