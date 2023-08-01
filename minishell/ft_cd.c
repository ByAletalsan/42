/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:46:40 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/27 18:08:45 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

static int	ft_set_path(char *path)
{
	char	*aux;

	if (!ft_strcmp(path, "~"))
	{
		aux = export_value("HOME");
		if (!aux)
			return (printf("HOMELESS!\n"), 1);
		if (chdir(aux) < 0)
			return (free(aux), 1);
		free(aux);
	}
	else if (chdir(path) < 0)
		return (1);
	return (0);
}

static int	ft_old_pwd(char *path)
{
	t_list	*list;
	char	*aux;

	list = find_node_enviro_with_key("OLDPWD", g_varbox->enviroment);
	if (!list)
		return (0);
	free(list->content);
	aux = ft_strjoin("OLDPWD=", path);
	if (!aux)
		return (1);
	list->content = aux;
	return (0);
}

static int	ft_new_pwd(char *path)
{
	t_list	*list;
	char	*aux;

	list = find_node_enviro_with_key("PWD", g_varbox->enviroment);
	if (!list)
		return (0);
	free(list->content);
	aux = ft_strjoin("PWD=", path);
	if (!aux)
		return (1);
	list->content = aux;
	return (0);
}

static int	ft_get_path(char *path, char **split, char **cmd_opt, int i)
{
	path = ft_clean_bars(cmd_opt[1], 0, 0, 0);
	if (!path)
		return (1);
	if (path[0] != '/')
	{
		split = ft_split(path, '/');
		if (!split)
			return (free(path), 1);
		while (split[++i])
		{
			if (ft_set_path(split[i]))
				return (ft_free_params(split), free(path),
					printf("File or directory doesn't exist\n"), 1);
		}
		ft_free_params(split);
	}
	else
	{
		if (ft_set_path(path))
			return (printf("File or directory doesn't exist\n"),
				free(path), 1);
	}
	return (free(path), 0);
}

int	ft_cd(char **cmd_opt)
{
	char	*aux;

	if (ft_len_matrix2(cmd_opt) > 2)
		return (printf("Too arguments!\n"), 1);
	else if (ft_len_matrix2(cmd_opt) < 2)
	{
		aux = export_value("HOME");
		if (!aux)
			return (printf("HOMELESS!\n"), 1);
		if (ft_set_path(aux))
			return (free(aux), 1);
		free(aux);
	}
	else if (ft_len_matrix2(cmd_opt) == 2)
	{
		if (ft_get_path(0, 0, cmd_opt, -1))
			return (1);
	}
	if (ft_old_pwd(g_varbox->path))
		return (1);
	getcwd(g_varbox->path, 1024);
	if (ft_new_pwd(g_varbox->path))
		return (1);
	return (0);
}
