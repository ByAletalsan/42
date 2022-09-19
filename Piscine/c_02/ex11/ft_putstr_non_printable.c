/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:27:59 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/15 11:57:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_char_to_hex(unsigned char c, char *hex)
{
	int			operation;
	char		p;

	hex[0] = '\\';
	p = 'a';
	operation = c % 16;
	if (operation <= 9)
		hex[2] = '0' + operation;
	else
		hex[2] = p + (operation - 10);
	operation = c / 16;
	if (operation <= 9)
		hex[1] = operation + '0';
	else
		hex[1] = p + (operation - 10);
	return ;
}

void	ft_putstr_non_printable(char *str)
{
	int				i;
	char			hex[3];
	unsigned char	c;

	i = 0;
	c = str[i];
	while (c != '\0')
	{
		if (c < 32 || c > 126)
		{
			ft_char_to_hex(c, hex);
			write(1, hex, 3);
		}
		else
			write(1, &c, 1);
		c = str[++i];
	}
	return ;
}
