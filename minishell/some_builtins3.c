/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_builtins3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:50:52 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/26 21:49:45 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

int	ft_check_var_name(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (!i && !ft_isalpha(s[i]))
			return (0);
		if (i)
		{
			if (!ft_isalnum(s[i]) && !(s[i] == '_'))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_walk_bars(char *path, int i)
{
	while (path[i] == '/')
				i++;
	return (i);
}

char	*ft_clean_bars(char *path, int i, char *aux_join, char *aux)
{
	char	*final_path;

	final_path = (char *)ft_calloc(1, 1);
	if (!final_path)
		return (NULL);
	while (path[i])
	{
		aux_join = (char *)ft_calloc(2, 1);
		if (!aux_join)
			return (free(final_path), NULL);
		aux_join[0] = path[i];
		aux = final_path;
		final_path = ft_strjoin(final_path, aux_join);
		free(aux_join);
		free(aux);
		if (!final_path)
			return (NULL);
		if (path[i] == '/')
			i = ft_walk_bars(path, i);
		else
			i++;
	}
	return (final_path);
}

static t_list	*ft_lstdel_last(t_list **list)
{
	t_list	*aux;
	t_list	*first;

	first = *list;
	if (!(*list)->next)
	{
		free((*list));
		return (NULL);
	}
	while ((*list)->next->next)
		(*list) = (*list)->next;
	aux = (*list)->next;
	(*list)->next = NULL;
	free(aux);
	return (first);
}

int	ft_unset(char **cmd_opt)
{
	t_list	*var;
	int		i;
	int		code;

	i = 0;
	code = 0;
	while (cmd_opt[++i])
	{
		if (!ft_check_var_name(cmd_opt[i]) || cmd_opt[i][0] == '=')
			code = ft_no_valid_name();
		var = find_node_enviro_with_key(cmd_opt[i], g_varbox->enviroment);
		if (var)
		{
			free (var->content);
			while (var->next)
			{
				var->content = var->next->content;
				var = var->next;
			}
			g_varbox->enviroment = ft_lstdel_last(&(g_varbox->enviroment));
		}
	}
	return (code);
}
