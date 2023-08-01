/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:24:37 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/28 18:31:05 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

extern t_varbox	*g_varbox;

char	*search_wc(int i, int j, char *line, int *q)
{
	char	*aux;
	char	*res;
	t_list	*list;

	if (!q[1] && line[i - 1] == '*')
	{
		while (j >= 0 && !ft_isspace(line[j]))
			j--;
		while (line[i] && !ft_isspace(line[i]))
			i++;
		aux = ft_substr(line, j + 1, i);
		if (!aux)
			return (free(line), NULL);
		list = wildcard_gestor(aux);
		free(aux);
		if (list)
		{
			res = insert_list(line, list, j + 1, &i);
			ft_lstclear(&list, free_content_lst);
			if (!res)
				return (NULL);
			return (res);
		}
	}
	return (line);
}

char	*insert_content(char *res, t_list *list, int *len)
{
	char	*aux;

	aux = res;
	res = ft_strjoin(res, (char *)list->content);
	free(aux);
	if (!res)
		return (NULL);
	*len += ft_strlen((char *)list->content);
	if (list->next)
	{
		aux = res;
		res = ft_strjoin(res, " ");
		free(aux);
		if (!res)
			return (NULL);
		(*len)++;
	}
	return (res);
}

char	*insert_list(char *line, t_list *list, int j, int *i)
{
	char	*res;
	char	*aux;
	char	*aux2;
	int		len;

	res = ft_substr(line, 0, j);
	if (!res)
		return (free(line), NULL);
	len = 0;
	while (list)
	{
		res = insert_content(res, list, &len);
		if (!res)
			return (free(line), NULL);
		list = list->next;
	}
	aux = res;
	aux2 = ft_substr(line, *i + 1, ft_strlen(line));
	res = ft_strjoin(res, aux2);
	free(aux);
	free(aux2);
	if (!res)
		return (free(line), NULL);
	*i += len;
	return (free(line), res);
}

int	ft_lim_bash(char c)
{
	if (c != '|' && c != '&' && c != '(' && c != ')'
		&& c != '<' && c != '>' && c != '#')
		return (1);
	return (0);
}

int	check_sintax(char *s, char c, int i)
{
	int	count;

	i++;
	if (s[i] == c)
		i++;
	count = 0;
	while (s[i] && ft_lim_bash(s[i]))
	{
		if (!ft_isspace(s[i]))
			count++;
		i++;
	}
	return (count);
}
