/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:25:59 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/27 16:06:00 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clean_cmd.h"
#include "libft/libft.h"
#include "types.h"

static int	ft_count_bars(char *cmd)
{
	int	i;
	int	count;
	int	*q;

	q = (int *)ft_calloc(2, sizeof(int));
	if (!q)
		return (actualizar_exit_code(1), 1);
	i = 0;
	count = 0;
	while (cmd[i])
	{
		quotes(cmd[i], q);
		if (cmd[i] == '(' && !q[1])
			count++;
		else if (cmd[i] == ')' && !q[1])
			count--;
		if (count < 0)
			return (free(q), actualizar_exit_code(1), 1);
		i++;
	}
	if (count)
		actualizar_exit_code(1);
	return (free(q), count);
}

static char	*ft_straight_bars(char *cmd)
{
	int		len;
	char	*aux;
	char	*aux2;

	aux = clean_spaces(cmd);
	free(cmd);
	cmd = NULL;
	len = ft_strlen(aux);
	while (!ft_count_bars(aux) && aux[0] == '(' && aux[len - 1] == ')')
	{
		if (cmd)
			free(cmd);
		cmd = clean_spaces(aux);
		aux2 = aux;
		aux = ft_substr(aux, 1, len - 2);
		free(aux2);
		len = ft_strlen(aux);
	}
	if (!ft_count_bars(aux))
	{
		if (cmd)
			free(cmd);
		cmd = ft_strdup(aux);
	}
	return (free(aux), cmd);
}

static int	ft_check_operators(char *cmd, int i, int *q)
{
	q = (int *)ft_calloc(2, sizeof(int));
	if (!q)
		return (actualizar_exit_code(1), 1);
	while (cmd[++i])
	{
		quotes(cmd[i], q);
		if (cmd[i] == '&' && !q[1])
		{
			if (ft_strncmp(&cmd[i], "&&", 2))
				return (free(q), actualizar_exit_code(258), 1);
			else
				i++;
			if (ft_check_left_rigth(i, cmd))
				return (free(q), actualizar_exit_code(258), 1);
		}
		else if (cmd[i] == '|' && !q[1])
		{
			if (!ft_strncmp(&cmd[i], "||", 2))
				i++;
			if (ft_check_left_rigth(i, cmd))
				return (free(q), actualizar_exit_code(258), 1);
		}
	}
	return (free(q), 0);
}

static int	ft_check_comillas(char *cmd, int i)
{
	int		*q;

	q = (int *)ft_calloc(2, sizeof(int));
	if (!q)
		return (actualizar_exit_code(1), 1);
	while (cmd[i])
		quotes(cmd[i++], q);
	if (q[1])
		return (free(q), actualizar_exit_code(1), 1);
	return (free(q), 0);
}

char	*ft_cpy_cmd_clean(char *cmd_ln, int i, char *aux2)
{
	char	*aux;

	if (!ft_strlen(cmd_ln))
		return (cmd_ln);
	while (cmd_ln[i] && ft_isspace(cmd_ln[i]))
		i++;
	if (!cmd_ln[i])
		return (cmd_ln);
	if (ft_check_comillas(cmd_ln, 0))
		return (free(cmd_ln), printf("Error comillas\n"), NULL);
	if (ft_check_operators(cmd_ln, -1, NULL))
		return (free(cmd_ln), printf("Invalid operators\n"), NULL);
	if (ft_count_bars(cmd_ln))
		return (free(cmd_ln), printf("Invalid ()\n"), NULL);
	aux = ft_straight_bars(cmd_ln);
	if (!aux)
		return (NULL);
	aux2 = clean_spaces(aux);
	if (!aux2)
		return (free(aux), NULL);
	if (ft_strlen(aux2) > 0)
		return (free(aux), aux2);
	else
		return (free(aux), free(aux2), actualizar_exit_code(1),
			printf("Invalid ()\n"), NULL);
}
