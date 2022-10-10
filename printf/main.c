#include <stdio.h>
#include "ft_printf.h"

int main()
{
	ft_printf(" %.1s %.2s %.3s %.4s \n", " - ", "", "4");
	printf(" %.1s %.2s %.3s %.4s \n", " - ", "", "4", "");
}