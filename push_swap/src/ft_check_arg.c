/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:10:04 by atalaver          #+#    #+#             */
/*   Updated: 2022/11/08 17:45:32 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	ft_check_rep(t_pila *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->len)
	{
		j = i + 1;
		while (j < a->len)
		{
			if (a->p[i] == a->p[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_limit(int argc, char **argv)
{
	int		i;
	int		j;
	char	**s;
	long	n;

	i = 1;
	while (i < argc)
	{
		j = 0;
		s = ft_split((const char *)argv[i], ' ');
		while (s[j] != NULL)
		{
			n = ft_atol(s[j]);
			if (n > INT_MAX || n < INT_MIN)
			{
				free(s);
				return (1);
			}
			j++;
		}
		free(s);
		i++;
	}
	return (0);
}

static int	ft_check_digit_two(char *p, char **s)
{
	while (*p == '-' || *p == '+')
		p += 1;
	if (*p == '\0')
	{
		free(s);
		return (1);
	}
	while (*p != '\0')
	{
		if (!ft_isdigit(*p))
		{
			if (*p != ' ')
			{
				free(s);
				return (1);
			}
		}
		p += 1;
	}
	return (0);
}

int	ft_check_digit(int argc, char **argv)
{
	int		i;
	int		j;
	char	**s;
	char	*p;

	i = 1;
	while (i < argc)
	{
		j = 0;
		s = ft_split((const char *)argv[i], ' ');
		p = s[0];
		while (s[j] != NULL)
		{
			if (ft_check_digit_two(p, s))
				return (1);
			p = s[++j];
		}
		free(s);
		i++;
	}
	return (0);
}
