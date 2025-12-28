#define std_asset(expr) (expr ? (void)0 : std_assertfail(#expr))
static void std_assertfail(const char *expr)
{
	write(2, "Assertion Failure: ", 19); 
	write(2, expr, ft_strlen(expr));
	raise(SIGABRT);
}
int main()
{
	std_assertfail("here is my work");
}
