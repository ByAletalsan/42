/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:53:00 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/26 17:37:55 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

char	*export_value(char *var)
{
	char	**aux;
	char	*value;
	t_list	*enviroment;

	value = NULL;
	enviroment = g_varbox->enviroment;
	while (enviroment)
	{
		aux = ft_split(enviroment->content, '=');
		if (!aux)
			return (ft_free_params(aux), NULL);
		if (ft_strcmp(aux[0], var) == 0)
		{
			value = ft_strdup(aux[1]);
			if (!value)
				return (ft_free_params(aux), NULL);
			return (ft_free_params(aux), value);
		}
		ft_free_params(aux);
		enviroment = enviroment->next;
	}
	return (NULL);
}

char	*constructor(int j, int i, char *line)
{
	char	*aux;
	char	*first;
	char	*final;
	char	*expanded;

	if (ft_isdigit(line[i]) || line[i] == '?')
		j++;
	else
	{
		while (line[j] != '\0' && (ft_isalnum(line[j]) || (j == i
					&& line[j] == '?')))
			j++;
	}
	aux = ft_substr(line, i, j - i);
	expanded = export_value(aux);
	free(aux);
	first = ft_substr(line, 0, i - 1);
	final = ft_substr(line, j, ft_strlen(line));
	aux = ft_strjoin(first, expanded);
	free(first);
	first = line;
	line = ft_strjoin(aux, final);
	free(first);
	free(expanded);
	return (free(final), free(aux), line);
}

char	*expand_envar(char *line)
{
	int		i;
	int		*q;

	i = 0;
	q = (int *)ft_calloc(2, sizeof(int));
	if (q == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if (!quotes(line[i++], q))
		{
			if (q[0] != '\'' && line[i - 1] == '$')
			{
				line = constructor(i, i, line);
				i = 0;
			}
		}
	}
	return (free(q), line);
}
