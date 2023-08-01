/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procreacion2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:36:36 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/27 14:34:16 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

void	aumentar_profundidad(t_list *list, int shlvl, char *aux2,
	char *aux3)
{
	t_list	*aux;

	if (aux2)
	{
		shlvl = ft_atoi(aux2) + 1;
		free(aux2);
	}
	aux2 = ft_itoa(shlvl);
	if (!aux2)
		return ;
	aux3 = ft_strjoin("SHLVL=", aux2);
	free(aux2);
	if (!aux3)
		return ;
	list = find_node_enviro_with_key("SHLVL", g_varbox->enviroment);
	if (!list)
	{
		aux = ft_lstnew(aux3);
		if (!aux)
			return ;
		ft_lstadd_back(&g_varbox->enviroment, aux);
		return ;
	}
	free(list->content);
	list->content = aux3;
}

int	is_builtin(char **cmd_opt)
{
	if (ft_len_matrix2(cmd_opt) > 0)
	{
		if (!ft_strcmp(cmd_opt[0], "pwd"))
			return (1);
		else if (!ft_strcmp(cmd_opt[0], "exit"))
			return (2);
		else if (!ft_strcmp(cmd_opt[0], "env"))
			return (3);
		else if (!ft_strcmp(cmd_opt[0], "export"))
			return (4);
		else if (!ft_strcmp(cmd_opt[0], "echo"))
			return (5);
		else if (!ft_strcmp(cmd_opt[0], "unset"))
			return (6);
		else if (!ft_strcmp(cmd_opt[0], "cd"))
			return (7);
	}
	return (0);
}

int	ft_exec_builtin(t_ejevars *v, char **cmd_opt)
{
	if (v->builtin == 1)
		return (ft_pwd(cmd_opt));
	else if (v->builtin == 2)
		return (ft_exit(cmd_opt, NULL));
	else if (v->builtin == 3)
		return (ft_env(cmd_opt));
	else if (v->builtin == 4)
		return (ft_export(cmd_opt, NULL));
	else if (v->builtin == 5)
		return (ft_echo(cmd_opt));
	else if (v->builtin == 6)
		return (ft_unset(cmd_opt));
	else if (v->builtin == 7)
		return (ft_cd(cmd_opt));
	return (0);
}

int	builtin(t_ejevars *v, int **pipes, char **cmd_opt)
{
	int	saved;

	saved = dup(STDOUT_FILENO);
	if (v->tp.control_i)
	{
		actualizar_exit_code(1);
		return (v->i++, printf("ERROR DE ENTRADA\n"), 1);
	}
	if (v->tp.fs > 0)
	{
		dup2(v->tp.fs, STDOUT_FILENO);
		close(v->tp.fs);
	}
	else if (v->j > 0)
	{
		if (v->i < v->npipes)
		{
			dup2(pipes[v->i][1], STDOUT_FILENO);
			close(pipes[v->i][1]);
		}
	}
	v->status = ft_exec_builtin(v, cmd_opt);
	dup2(saved, STDOUT_FILENO);
	return (actualizar_exit_code(v->status), 0);
}

char	**env_to_matrix(t_list *list, int i)
{
	char	**res;
	t_list	*code;
	t_list	*name;

	list = g_varbox->enviroment;
	code = find_node_enviro_with_key("?", g_varbox->enviroment);
	name = find_node_enviro_with_key("0", g_varbox->enviroment);
	res = ft_calloc(ft_len_list(list) - 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (list)
	{
		if (list == name || list == code)
		{
			list = list->next;
			continue ;
		}
		res[i] = ft_strdup(list->content);
		if (!res[i])
			return (ft_free_params(res), NULL);
		list = list->next;
		i++;
	}
	return (res);
}
