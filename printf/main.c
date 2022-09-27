#include "libftprintf.h"
#include <stdio.h>

int	ft_ptr_len(unsigned long long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_ptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	print_length;

	print_length = 0;
	print_length += write(1, "0x", 2);
	if (ptr == 0)
		print_length += write(1, "0", 1);
	else
	{
		ft_put_ptr(ptr);
		print_length += ft_ptr_len(ptr);
	}
	return (print_length);
}

int main()
{

	/*int x = ft_printf("%% Hola %s, que tal estas%c %+i\n", "Paquito", '?', 10);
	int y = printf("%% Hola %s, que tal estas%c %+i\n", "Paquito", '?', 10);
	printf("%i\n", x);
	printf("%i\n", y);*/
	int x = ft_print_ptr((unsigned long long)&x);
	printf("\n");
	int y = ft_printf("%p\n", &x);
	printf("X: %i\nY: %i\n", x, y);
	return (0);
}