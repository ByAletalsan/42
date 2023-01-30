/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:10:04 by atalaver          #+#    #+#             */
/*   Updated: 2023/01/30 15:52:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	ft_free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

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
				ft_free_split(s);
				return (1);
			}
			j++;
		}
		ft_free_split(s);
		i++;
	}
	return (0);
}

static int	ft_check_digit_two(char *p)
{
	while (*p == '-' || *p == '+')
		p += 1;
	if (*p == '\0')
		return (1);
	while (*p != '\0')
	{
		if (!ft_isdigit(*p))
		{
			if (*p != ' ')
				return (1);
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
		if (!s[0])
			return (1);
		p = s[0];
		while (s[j] != NULL)
		{
			if (ft_check_digit_two(p))
				return (ft_free_split(s), 1);
			p = s[++j];
		}
		ft_free_split(s);
		i++;
	}
	return (0);
}
