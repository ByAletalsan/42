#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	long x = 0;
	char *s = "%u\n";
	int r = printf(s, x);
	int p = ft_printf(s, x);
	printf("Normal: %i ,Mio: %i\n", r, p);
}