/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:48:38 by atalaver          #+#    #+#             */
/*   Updated: 2022/09/19 14:05:33 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c == 32)
		return (1);
	if (c < 33 || c > 126)
		return (0);
	return (1);
}
