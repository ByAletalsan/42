/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:32:59 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/14 22:28:54 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_count_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	size_src;
	unsigned int	size_dest;

	i = 0;
	j = 0;
	size_src = ft_count_char(src);
	size_dest = ft_count_char(dest);
	while (dest[i] > 0 && i < size)
		i++;
	while (i < size - 1 && size != 0 && src[j] > 0)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (size <= size_dest)
		return (size_src + size);
	else
	{
		dest[i] = '\0';
		return (size_dest + size_src);
	}
}
