#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "vector.h"

typedef struct s_hitRec {
	t_vec p;
	t_vec normal;
	double t;
}	t_hitRec;

typedef struct s_obj {
	int	type;
} t_obj;

#endif
