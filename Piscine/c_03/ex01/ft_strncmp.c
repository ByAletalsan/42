/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 12:55:50 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/17 19:14:55 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<string.h>

void	ft_truncar(int	*p)
{
	if (*p > 0)
		*p = 1;
	else if (*p < 0)
		*p = -1;
	else
		*p = 0;
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	int				res;

	i = 0;
	res = 0;
	if (n == 0)
		return (0);
	while (!res && (s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		res = s1[i] - s2[i];
		if (!res)
			i++;
	}
	if (i < n)
	{
		res = s1[i] - s2[i];
	}
	ft_truncar(&res);
	return (res);
}

int main(){
	char s1[] = "abcdef";
	char s2[] = "accdff";

	printf("%d\n", ft_strncmp(s1, s2, 2));
	printf("%d\n", strncmp(s1, s2, 2));
}
