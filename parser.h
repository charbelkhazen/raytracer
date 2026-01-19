//TODO: riaseError() uses io (write !). how can I delegate this to client
//TODO:  PARSE LIGHT () SHOULD FILL T_LIGHT THIS IS WRONG
//TODO:  Change name of consumeNumber and Comma to parse (i.e. raises err too)
#ifndef PARSER_H
# define PARSER_H
# include "vector.h"
# include "light.h"

void	pars_skipWhiteSpace(char **ptr_buf);

//consumes and returns type as int (which corresponds to first char of of type)
int	pars_consumeType(char **ptr_buf);

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
#endif
