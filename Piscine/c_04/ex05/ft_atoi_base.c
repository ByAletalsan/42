/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:07:26 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/21 18:10:37 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_error_base(char *base)
{
	int	base_len;
	int	i;
	int	j;

	base_len = ft_strlen(base);
	i = 0;
	if (base_len <= 1)
		return (1);
	while (base[i] != '\0')
	{
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[j] == base[i])
				return (1);
			if (base[j] == '+' || base[j] == '-')
				return (1);
			if (base[j] == '\t' || base[j] == '\n' || base[j] == '\v'
				|| base[j] == '\f' || base[j] == '\r' || base[j] == ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_pow(int base, int exponent)
{
	int	result;

	result = 1;
	while (exponent > 0)
	{
		result *= base;
		exponent--;
	}
	return (result);
}

void	ft_number(int i, int *n, char *str, char *base)
{
	int	c;
	int	control;
	int	j;

	c = i;
	while (str[++i] != '\0' && control != 0)
	{
		j = 0;
		control = 0;
		while (base[j] != '\0')
		{
			if (str[i] == base[j++])
			{
				control = 1;
				break ;
			}
		}
	}
	while (++c < i)
	{
		if (str[c] > '9' && str[c] <= 90)
			*n += (str[c] - 55) * ft_pow(ft_strlen(base), (i - c) - 1);
		else if (str[c] >= 97 && str[c] <= 122)
			*n += (str[c] - 97) * ft_pow(ft_strlen(base), (i - c) - 1);
		else
			*n += (str[c] - '0') * ft_pow(ft_strlen(base), (i - c) - 1);
	}
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	number;
	int	signo;

	i = 0;
	number = 0;
	signo = 1;
	if (ft_error_base(base) == 1)
		return (0);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signo *= -1;
		i++;
	}
	ft_number(i - 1, &number, str, base);
	return (number * signo);
}

int main()
{
	printf("%d\n", ft_atoi_base("u", "poniguay"))
}