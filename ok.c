#include <math.h>
int	std_cmpDouble(double a, double b, double eps)
{
	if (fabs(a - b) < eps)
		return (1);
	return (0);
}

#include <stdio.h>
int main()
{
	printf("%d\n", std_cmpDouble(0.1 + 0.2, 0.3, 1e-9));
}
