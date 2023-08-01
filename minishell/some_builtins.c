/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:48:27 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/27 14:21:51 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

int	ft_no_valid_name(void)
{
	return (printf("Not valid name\n"), 1);
}

static void	ft_change_content(t_list *aux, char *cont)
{
	free(aux->content);
	aux->content = cont;
}

static int	ft_valid_name(int *code, char **cmd_opt, t_list *lista, int i)
{
	t_list	*aux;
	char	**var_val;
	char	*cont;

	var_val = ft_split(cmd_opt[i], '=');
	if (!var_val)
		return (1);
	if (!ft_check_var_name(var_val[0]) || cmd_opt[i][0] == '=')
		*code = ft_no_valid_name();
	else
	{
		aux = find_node_enviro_with_key(var_val[0], lista);
		cont = ft_strdup(cmd_opt[i]);
		if (aux)
			ft_change_content(aux, cont);
		else
		{
			aux = ft_lstnew(cont);
			if (!aux)
				return (free(cont), ft_free_params(var_val), 1);
			ft_lstadd_back(&lista, aux);
		}
	}
	ft_free_params(var_val);
	return (0);
}

static int	ft_export_args(char **cmd_opt, int i, t_list *lista)
{
	int		code;

	code = 0;
	while (cmd_opt[++i])
	{
		if (ft_strchr(cmd_opt[i], '='))
		{
			if (ft_valid_name(&code, cmd_opt, lista, i))
				return (1);
		}
		else if (!ft_check_var_name(cmd_opt[i]) || cmd_opt[i][0] == '=')
			code = ft_no_valid_name();
	}
	return (code);
}

int	ft_export(char **cmd_opt, char **split)
{
	t_list	*lista;
	t_list	*code;
	t_list	*name;

	lista = g_varbox->enviroment;
	code = find_node_enviro_with_key("?", g_varbox->enviroment);
	name = find_node_enviro_with_key("0", g_varbox->enviroment);
	if (!cmd_opt[1])
	{
		while (lista)
		{
			if (lista != code && lista != name)
			{
				split = ft_split(lista->content, '=');
				if (!split)
					return (1);
				printf("declare -x %s=\"%s\"\n", split[0], split[1]);
				ft_free_params(split);
			}
			lista = lista->next;
		}
	}
	else
		return (ft_export_args(cmd_opt, 0, g_varbox->enviroment));
	return (0);
}
