/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:00:13 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/12 16:33:40 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] > 0)
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	control;

	i = 0;
	control = 1;
	ft_strlowcase(str);
	while (str[i] > 0)
	{
		if (str[i] >= 97 && str[i] <= 122 && control)
		{
			str[i] -= 32;
			control = 0;
		}
		else if (str[i] < 97 || str[i] > 122)
			control = 1;
		if (str[i] >= 48 && str[i] <= 57)
			control = 0;
		i++;
	}
	return (str);
}
