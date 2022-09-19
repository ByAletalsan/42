/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:03:15 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/28 21:28:48 by atalaver         ###   ########.fr       */
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
	int	str_len;

	str_len = ft_strlen(argv[0]);
	if (argc >= 1 && argv[0][0] != '\0')
	{
		write(1, argv[0], str_len);
		write(1, "\n", 1);
	}
	return (0);
}
