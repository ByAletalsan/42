/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:32:29 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/28 14:33:27 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ten_queens_puzzle(void)
{
	int	i;
	int	nb;

	nb = 8;
	if (nb < 2)
		return (0);
	if (nb == 2)
		return (1);
	if (nb % 2 == 0)
		return (0);
	i = 2;
	while ((i * i) <= nb && i < 43340)
		i++;
	while (i > 1)
	{
		if (nb % i == 0)
			return (0);
		i--;
	}
	return (1);
}
