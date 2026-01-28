//TODO: riaseError() uses io (write !). how can I delegate this to client
//TODO:  PARSE LIGHT () SHOULD FILL T_LIGHT THIS IS WRONG
//TODO:  Change name of consumeNumber and Comma to parse (i.e. raises err too)
//TODO:  Make it explicit that some of the parsers (e.g. parse light and camera ...) do take into consideration whitespace OR REMOVE THE WHITESPACE AND DELEGATE IT TO PARSELINE
#ifndef PARSER_H
# define PARSER_H
# include "vector.h"
# include "light.h"
# include "ambientlight.h"
# include "viewer.h"
# include "object.h"
# include "sphere.h"
# include "material.h"

// these are the fields that user can fill through .rt
// they generalize to t_scene
typedef struct s_parsables
{
	t_light light;
	t_amb	amb;
	t_view	view;
	t_obj	obj;
}	t_parsables;

typedef enum
{
	CAMERA_CMD;
	LIGHT_CMD;
	AMBIENT_CMD;
	OBJECT_CMD;
}	t_cmd_type;

void	pars_skipWhiteSpace(char **ptr_buf);

//STRICT CONTRACT: PTR_BUF MUST BE NUL TERMINATED
//type is case sensitive : 'c' : cylinder != 'C' : camera
//assumes no whitespace, consumes and advances the type
int	pars_consumeType(int *type, char **ptr_buf);

//assumes no whitespaces. Consume number and advances. double parsing relies on atod, returns 1 on err
int	pars_consumeNumber(double *num, char **buf);

//assumes no whitespaces. Consume int and advances. int parsing relies on atoi, returns 1 on err
int	pars_consumeInteger(int *num, char **buf);

//No whitespace assumptoin. consume comma. If no comma return (1) (parsin err)
int	pars_consumeComma(char **buf);

//assumes comma seperation between them, allows for whitespace between numbers
int	pars_consume3Numbers(t_vec *vector, char **buf);

int	pars_consume3Integers(t_vec *vector, char **buf);

int	pars_consumeMandatoryWhiteSpace(char **buf);

int	pars_checkColorRange(t_vec color);

int	pars_checkUnitIntervalRange(double num);

int	pars_parseLight(t_light *light, char *buf);

int	pars_parseAmbient(t_ambientLight *ambient, char *buf);

int	pars_parseCamera(t_viewer *view, char *buf);

int	pars_parseSphere(t_obj *obj, t_sph *sphere, t_mat *material, char *buf);
#endif
