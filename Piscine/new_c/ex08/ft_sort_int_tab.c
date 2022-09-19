/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 12:48:41 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/10 12:56:48 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	_i_menor(int *tab, int size, int i)
{
	int	n_menor;
	int	i_menor;

	n_menor = tab[i];
	i_menor = i;
	i++;
	while (i < size)
	{
		if (tab[i] < n_menor)
		{
			n_menor = tab[i];
			i_menor = i;
		}
		i++;
	}
	return (i_menor);
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	i_menor;
	int	aux;

	i = 0;
	while (i < size)
	{
		i_menor = _i_menor(tab, size, i);
		aux = tab[i];
		tab[i] = tab[i_menor];
		tab[i_menor] = aux;
		i++;
	}	
}
