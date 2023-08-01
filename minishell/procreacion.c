/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procreacion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:47:46 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/28 18:02:36 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

static void	ft_execve(char *route, char **cmd_opt, char **env)
{
	if (execve(route, cmd_opt, env) < 0)
	{
		ft_free_params(env);
		printf("ERROR CABRON...\n");
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		exit(1);
	}
}

static void	hijo2(t_ejevars *v, int **pipes, char *route, char **cmd_opt)
{
	char	**env;

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
	if (!ft_len_matrix2(cmd_opt))
		exit(0);
	env = env_to_matrix(NULL, 0);
	if (!env)
		exit(1);
	ft_execve(route, cmd_opt, env);
}

static int	hijo(t_ejevars *v, int **pipes, char *route, char **cmd_opt)
{
	if (v->tp.fi > 0)
	{
		dup2(v->tp.fi, STDIN_FILENO);
		close(v->tp.fi);
	}
	else if (v->tp.ft > 0)
	{
		dup2(v->tp.ft, STDIN_FILENO);
		close(v->tp.ft);
	}
	else if (v->j >= 0)
	{
		if (v->i < v->npipes)
			close(pipes[v->i][0]);
		if (v->i > 0)
		{
			dup2(pipes[v->i - 1][0], STDIN_FILENO);
			close(pipes[v->i - 1][0]);
		}
		if (v->tp.control_i)
			return (v->i++, printf("ERROR DE ENTRADA\n"), 1);
	}
	hijo2(v, pipes, route, cmd_opt);
	return (0);
}

static void	papa(t_ejevars *v, int **pipes, char *route, char **cmd_opt)
{
	if (v->npipes > 0)
	{
		if (v->i < v->npipes)
			close(pipes[v->i][1]);
		if (v->i > 0)
			close(pipes[v->i - 1][0]);
	}
	g_varbox->flag_c = 1;
	waitpid(v->pid, &v->status, 0);
	actualizar_exit_code(WEXITSTATUS(v->status));
	if (g_varbox->flag_c == 2)
		actualizar_exit_code(130);
	else
		g_varbox->flag_c = 0;
	ft_free_params(cmd_opt);
	if (v->control_route)
		free(route);
}

int	procrear(t_ejevars *v, char **inpipes, int **pipes, char **cmd_opt)
{
	v->builtin = is_builtin(cmd_opt);
	if (v->builtin)
	{
		builtin(v, pipes, cmd_opt);
		ft_free_params(cmd_opt);
		if (v->control_route)
			free(v->route);
	}
	else
	{
		v->pid = fork();
		if (v->pid < 0)
			return (ft_freedom(inpipes, cmd_opt, pipes, v->route), 1);
		else if (v->pid == 0)
		{
			if (hijo(v, pipes, v->route, cmd_opt))
				exit(1);
		}
		else
			papa(v, pipes, v->route, cmd_opt);
	}
	return (0);
}
