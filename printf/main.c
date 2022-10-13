#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -900;
	char *s = " %.1i \n";
	int r = printf(s, x);
	int p = ft_printf(s, x);
	printf("%i : %i\n", r, p);
}