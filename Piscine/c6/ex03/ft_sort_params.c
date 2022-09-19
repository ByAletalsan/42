/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 20:40:43 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/28 21:07:44 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	diff;

	diff = 0;
	i = 0;
	while (s1[i] > 0)
	{
		if (s1[i] != s2[i])
		{
			break ;
		}
		i++;
	}
	diff = s1[i] - s2[i];
	if (diff != 0)
		return (s1[i] - s2[i]);
	else
		return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_n_max(int i, int argc, char **argv)
{
	int	n_max;
	int	j;

	j = i;
	n_max = i;
	while (j < argc)
	{
		if (ft_strcmp(argv[j], argv[n_max]) < 0)
			n_max = j;
		j++;
	}
	return (n_max);
}

int	main(int argc, char **argv)
{
	int		n_max;
	int		i;
	int		str_len;
	char	*aux;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			n_max = ft_n_max(i, argc, argv);
			aux = argv[i];
			argv[i] = argv[n_max];
			argv[n_max] = aux;
			str_len = ft_strlen(argv[i]);
			write(1, argv[i], str_len);
			write(1, "\n", 1);
			i++;
		}
	}
}
