/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gestion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:09:57 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/28 15:49:27 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

void	hijo_read_buffer(t_ficheros *tp, char *end)
{
	char	*new_line;
	char	*aux;

	g_varbox->flag_c = 2;
	new_line = readline("> ");
	if (!new_line)
		exit(0);
	while (new_line && ft_strcmp(new_line, end))
	{
		aux = ft_strjoin(new_line, "\n");
		write(tp->ft, aux, ft_strlen(aux));
		free(new_line);
		free(aux);
		new_line = readline("> ");
		if (!new_line)
			exit(0);
	}
	free(new_line);
	exit(0);
}

void	read_buffer(t_ficheros *tp, char *end)
{
	pid_t	pid;
	int		code;

	code = 0;
	pid = fork();
	if (pid < 0)
		return ;
	else if (!pid)
		hijo_read_buffer(tp, end);
	else if (pid > 0)
	{
		g_varbox->flag_c = 1;
		waitpid(pid, &code, 0);
		if (!code)
			g_varbox->flag_c = 0;
		else
			actualizar_exit_code(CODE_ERROR);
	}
}

static void	close_fin(t_ficheros *tp)
{
	if (tp->fi > 0)
	{
		close(tp->fi);
		tp->fi = 0;
	}
	if (tp->ft > 0)
	{
		close(tp->ft);
		tp->ft = 0;
	}
}

int	entrada(char *cmd, t_ficheros *tp, int type, char *name)
{
	int		len;

	name = search_name(cmd, 0);
	if (!name)
		return (0);
	len = ft_strlen(name);
	close_fin(tp);
	if (type == 0)
	{
		tp->control_i = 1;
		tp->fi = open(name, O_RDONLY);
	}
	if (type == 1)
	{
		if (!tp->f_word)
			tp->f_word = ft_strdup(name);
		else
		{
			free(tp->f_word);
			tp->f_word = ft_strdup(name);
		}
	}
	return (size_name(cmd, name, type, len));
}

int	salida(char *cmd, t_ficheros *tp, int type)
{
	char	*name;
	int		len;

	name = search_name(cmd, 0);
	if (!name)
		return (0);
	len = ft_strlen(name);
	if (tp->fs > 0)
	{
		close(tp->fs);
		tp->fs = 0;
	}
	if (type == 0)
		tp->fs = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0000777);
	else
		tp->fs = open(name, O_WRONLY | O_APPEND | O_CREAT, 0000777);
	return (size_name(cmd, name, type, len));
}
