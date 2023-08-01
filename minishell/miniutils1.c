/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniutils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:25:30 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/28 18:31:36 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

char	*clean_spaces(char *str)
{
	char	*newstr;
	int		i;
	int		j;
	int		*q;

	i = 0;
	j = 0;
	q = (int *)ft_calloc(2, sizeof(int));
	if (q == NULL)
		return (NULL);
	newstr = ft_strtrim((const char *)str, " ");
	if (newstr == NULL)
		return (free(q), NULL);
	while (newstr != NULL && newstr[i] != '\0')
	{
		newstr[j++] = newstr[i];
		if (!quotes(newstr[i++], q) && (!q[1] && newstr[i - 1] == ' '))
		{
			while (newstr[i] == ' ')
				i++;
		}
	}
	newstr[j] = '\0';
	return (free(q), newstr);
}

char	*strdeleted(char *s, int p1, int p2)
{
	int		len;
	char	*sub1;
	char	*sub2;
	char	*joined;
	char	*result;

	len = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((p1 < 0 || p1 > len - 1) || (p2 < 0 || p2 > len - 1) || p2 < p1)
		return (free(s), NULL);
	sub1 = ft_substr(s, 0, p1);
	if (!sub1)
		return (free(s), NULL);
	sub2 = ft_substr(s, p2 + 1, len - p2);
	if (!sub2)
		return (free(s), free(sub1), NULL);
	free(s);
	joined = ft_strjoin(sub1, sub2);
	if (!joined)
		return (free(sub1), free(sub2), NULL);
	result = clean_spaces(joined);
	if (!result)
		return (free(sub1), free(sub2), free(joined), NULL);
	return (free(sub1), free(sub2), free(joined), result);
}

static int	search_name_len(char *cmd, int **q)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	*q = (int *)ft_calloc(2, sizeof(int));
	if (!(*q))
		return (-1);
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\'' || cmd[i] == '"')
		quotes(cmd[i++], *q);
	while (cmd[i] != '\0' && (cmd[i] != ' ' || *(q + 1)))
	{
		if (!quotes(cmd[i], *q))
		{
			if (cmd[i] != (char)(**q))
				len++;
		}
		i++;
	}
	return (len);
}

char	*search_name(char *cmd, int len)
{
	int		n[2];
	char	*name;
	int		*q;

	n[0] = 0;
	n[1] = 0;
	name = (char *)ft_calloc((len = search_name_len(cmd, &q)) + 1, 1);
	if (len < 0)
		return (NULL);
	if (!name)
		return (free(q), NULL);
	while (cmd[n[0]] == ' ')
		n[0]++;
	if (cmd[n[0]] == '\'' || cmd[n[0]] == '"')
		quotes(cmd[n[0]++], q);
	while (cmd[n[0]] && (cmd[n[0]] != ' ' || q[1]) && ft_lim_bash(cmd[n[0]]))
	{
		if (!quotes(cmd[n[0]], q))
		{
			if (cmd[n[0]] != (char)q[0])
				name[n[1]++] = cmd[n[0]];
		}	
		n[0]++;
	}
	return (free(q), name);
}

t_list	*find_node_enviro_with_key(char *key, t_list *list)
{
	char	**aux_words;

	while (list)
	{
		aux_words = ft_split((char *)list->content, '=');
		if (!aux_words)
			return (NULL);
		if (!ft_strcmp(key, aux_words[0]))
		{
			ft_free_params(aux_words);
			return (list);
		}
		ft_free_params(aux_words);
		list = list->next;
	}
	return (list);
}
