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

//no whitespace skipping, expects +number -number only. e.g. "+12.12.12" is 12.12 ".12" returns 1 (err). "--12" returns 1 err 
int	std_atod(double *out, char *buf);
#endif
