/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:42:28 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/21 19:34:09 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
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
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_putnbr(int nbr, char *base, int base_len)
{
	if (nbr > (base_len - 1) || nbr < -(base_len - 1))
	{
		ft_putnbr(nbr / base_len, base, base_len);
		ft_putnbr(nbr % base_len, base, base_len);
	}
	else
	{
		if (nbr < 0)
			nbr *= -1;
		ft_putchar(base[nbr]);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	i;

	i = 0;
	if (ft_error_base(base) == 1)
		return ;
	if (nbr < 0)
	{
		write(1, "-", 1);
	}
	ft_putnbr(nbr, base, ft_strlen(base));
}
