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
