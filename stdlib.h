int	std_pow(int base, int power);
void	std_assert(int condition);
int	std_strlen(const char *string);
//must be used with std_itoa
int	std_sizeArray(int int_from_which_you_form_array);
/*arr points at at least std_sizeArray(int number) bytes*/
void	std_itoa(char *array, int number);
int	std_cmpDouble(double double1, double double2, double epsilon);
//must be used with std_dtoa
int	std_sizeArrayDouble(double double_from_which_you_form_array, int precision);
/*arr points at at least std_sizeArrayDouble(int number, precision) bytes*/
void	std_dtoa(char *arr, double n, int precision);


/*
#include <stdio.h>
int main()
{
	int	size;

	char arr[size];
	std_itoa(arr, -12);
	printf("%s\n", arr);
}
*/
/*
int main()
{
	int	size = std_sizeArrayDouble(10.23, 1);
	printf("size:%d\n", size);
	char	arr[100];

	std_dtoa(arr, -10.23, 1);
	printf("whole thing:%s\n", arr);
}
*/
