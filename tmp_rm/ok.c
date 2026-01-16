#include "parser.h"
#include <stdio.h>

void	run_test(char *buf)
{
	double num;
	
	printf("full buff:[%s]     ", buf);
	fflush(stdout);
	pars_consumeNumber(&num, &buf);
	printf("found number: %f\n", num);
	printf("   buf afre consume:<%s>\n", buf);
}


int main()
{
	run_test("+");
	//run_test("0");
	//run_test("0.0");
	//run_test("   0.0");
	//run_test("   0.0    1");
	//run_test("1+   0.0    1");
}
