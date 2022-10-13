#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -15;
	char *s = "%05i\n";
	int r = printf(s, x);
	int p = ft_printf(s, x);
	printf("%i : %i\n", r, p);
}