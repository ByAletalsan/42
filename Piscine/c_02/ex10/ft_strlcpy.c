/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:35:04 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/15 12:11:36 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_char(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] > 0)
	{
		count++;
		i++;
	}
	return (count);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	int				size_src;

	i = 0;
	size_src = ft_count_char(src);
	if (size > 0)
	{
		while (src[i] > 0 && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (size_src);
}
