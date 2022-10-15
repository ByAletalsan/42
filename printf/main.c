#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	int x = -8375;
	char *s = "%8.3i\n";
	int r = printf(s, x);
	int p = ft_printf(s, x);
	printf("Normal: %i ,Mio: %i\n", r, p);
}