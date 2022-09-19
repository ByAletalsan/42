/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:11:48 by atalaver          #+#    #+#             */
/*   Updated: 2022/07/10 20:21:41 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	rush(int x, int y);

int	elevado(int b, int e)
{
	int	resultado;

	resultado = 1;
	while (e > 0)
	{
		resultado *= b;
		e--;
	}
	return (resultado);
}

int	_negativo(char *str)
{
	if (str[0] == '-')
	{
		return (1);
	}
	return (0);
}

int	n_caracteres(char *str)
{
	char	c;
	int		i;
	int		count;

	i = 0;
	count = 0;
	c = str[i];
	while (c > 0)
	{
		count++;
		c = str[++i];
	}
	if (_negativo(str))
	{
		return (count - 1);
	}
	else
	{
		return (count);
	}
}

int	string_to_int(char *str)
{
	int		resultado;
	int		i;
	char	c;
	int		n;

	resultado = 0;
	n = n_caracteres(str) - 1;
	i = _negativo(str);
	c = str[i];
	while (c > 0)
	{
		resultado += (c - '0') * elevado(10, n);
		c = str[++i];
		n--;
	}
	if (_negativo(str) == 0)
	{
		return (resultado);
	}
	else
	{
		return (-resultado);
	}
}

int	main(int argc, char *argv[])
{
	int		filas;
	int		columnas;

	if (argc == 3)
	{
		filas = string_to_int(argv[1]);
		columnas = string_to_int(argv[2]);
		rush(filas, columnas);
	}
	return (0);
}
