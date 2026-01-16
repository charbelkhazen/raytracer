#ifndef STDLIB_H
#define STDLIB_H

int	std_pow(int base, int power);

void	std_assert(int condition);

int	std_strlen(const char *string);

int	std_cmpDouble(double double1, double double2, double epsilon);

/*arr points at at least std_sizeArray(int number) bytes*/
int	std_sizeArray(int int_from_which_you_form_array);
void	std_itoa(char *array, int number);

/*arr points at at least std_sizeArrayDouble(int number, precision) bytes*/
int	std_sizeArrayDouble(double double_from_which_you_form_array, int precision);
void	std_dtoa(char *arr, double n, int precision);

void	std_fillThenNull(char *arr, char c);

int	std_strlcpy(char *dst, const char *src, int size);

int	std_isWhiteSpace(char c);

int	std_isNum(char c);

//no whitespace skipping, expects +number -number only. returns nbytes consumed if return = 0 ->(err, no bytes consumed)
///e.g. "+12.12.12" , out becomes 12.12 return is 5 
///e.g. "+12." , out becomes 12 return is 3 ('+' '1' '2' are consumed) 
//"12." returns 2 and out of 12       ".12" returns 0 .                         "--12" returns 0 
int	std_atod(double *out, char *buf);
#endif
