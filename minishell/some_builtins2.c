/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:48:22 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/27 14:33:41 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

int	ft_pwd(char **cmd_opt)
{
	(void) cmd_opt;
	if (!getcwd(g_varbox->path, 1024))
		return (printf("Path's length is too long\n"), 1);
	ft_printf("%s\n", g_varbox->path);
	return (0);
}

int	ft_exit(char **cmd_opt, char *aux)
{
	g_varbox->exit = 1;
	if (ft_len_matrix2(cmd_opt) > 2)
	{
		aux = ft_strtrim(cmd_opt[1], " ");
		if (!aux)
			return (1);
		if (ft_is_full_digit(aux))
		{
			g_varbox->exit = 0;
			return (printf("exit\nToo much arguments!\n"), free(aux), 1);
		}
		else
			return (printf("exit\nArgument isn't a number!\n"), free(aux), 255);
	}
	else if (ft_len_matrix2(cmd_opt) == 2)
	{
		aux = ft_strtrim(cmd_opt[1], " ");
		if (!aux)
			return (1);
		if (ft_is_full_digit(aux))
			return (free(aux), printf("exit\n"), ft_atoi(cmd_opt[1]));
		else
			return (printf("exit\nArgument isn't a number!\n"), free(aux), 255);
	}
	return (printf("exit\n"), 0);
}

static int	check_n(char *option)
{
	int	i;

	if (!ft_strncmp("-n", option, 2))
	{
		i = 2;
		while (option[i] == 'n')
			i++;
		if (option[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_echo(char **cmd_opt)
{
	int	option;
	int	i;

	option = 0;
	i = 1;
	if (ft_len_matrix2(cmd_opt) > 1)
	{
		while (cmd_opt[i] && check_n(cmd_opt[i]))
		{
			option = 1;
			i++;
		}
		while (cmd_opt[i])
		{
			printf("%s", cmd_opt[i++]);
			if (cmd_opt[i])
				printf(" ");
		}
	}
	if (!option)
		printf("\n");
	return (0);
}

int	ft_env(char **cmd_opt)
{
	t_list	*lista;
	t_list	*code;
	t_list	*name;

	if (ft_len_matrix2(cmd_opt) >= 2)
		return (printf("Too much arguments!\n"), 1);
	lista = g_varbox->enviroment;
	ft_order_list(lista);
	code = find_node_enviro_with_key("?", g_varbox->enviroment);
	name = find_node_enviro_with_key("0", g_varbox->enviroment);
	while (lista)
	{
		if (lista != code && lista != name)
			printf("%s\n", (char *)lista->content);
		lista = lista->next;
	}
	return (0);
}
