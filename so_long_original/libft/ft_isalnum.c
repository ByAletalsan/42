/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:03:23 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/22 10:03:25 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c < 48 || c > 122)
		return (0);
	if (c > 57 && c < 65)
		return (0);
	if (c > 90 && c < 97)
		return (0);
	return (1);
}
