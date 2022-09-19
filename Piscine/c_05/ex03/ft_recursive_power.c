/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:29:52 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/28 14:03:29 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_power(int ab, int power)
{
	if (power < 0)
		return (0);
	if (ab == 0 || power == 0)
		return (1);
	if (power == 1)
		return (ab);
	return (ab * ft_recursive_power(ab, power - 1));
}
