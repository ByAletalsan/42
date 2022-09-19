/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:39:17 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/28 20:39:47 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int	i;
	int	str_len;

	i = argc - 1;
	if (argc > 1)
	{
		while (i > 0)
		{
			str_len = ft_strlen(argv[i]);
			write(1, argv[i], str_len);
			write(1, "\n", 1);
			i--;
		}
	}
}
