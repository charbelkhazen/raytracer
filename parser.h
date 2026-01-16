//TODO: riaseError() uses io (write !). how can I delegate this to client
//TODO:  PARSE LIGHT () SHOULD FILL T_LIGHT THIS IS WRONG
#ifndef PARSER_H
# define PARSER_H

void	pars_skipWhiteSpace(char **ptr_buf);

//consumes and returns type as int
int	pars_consumeType(char **ptr_buf);

//uses io!!
void	pars_raiseError(void);

//consume and fill
void	pars_consumeNumber(double *num, char **buf);

void	pars_consumeComma(char **buf);

//assumes comma seperation between them
void	pars_consume3Numbers(t_vec *vector, char **buf);

void	pars_consumeMandatoryWhiteSpace(char **buf);

void	pars_checkColorRange(t_vec color);

void	pars_checkUnitIntervalRange(double num);

void	pars_parseLight(char **buf);
#endif
