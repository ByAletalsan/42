/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:12:51 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/26 21:31:23 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

static int	creat_iwc(t_iwc *iwc, char *str, int i, int flag)
{
	iwc->nwc = 0;
	iwc->wci = 0;
	iwc->wcf = 0;
	while (str && str[++i] != '\0')
	{
		if (str[i] == '*')
		{
			if (flag == 0)
				iwc->nwc += 1;
			if (i == 0)
				iwc->wci = 1;
			if (str[i + 1] == '\0')
				iwc->wcf = 1;
			flag = 1;
		}
		else
			flag = 0;
	}
	if (iwc->nwc > 0)
	{
		iwc->ptrn = ft_split(str, '*');
		if (iwc->ptrn == NULL)
			return (1);
	}
	return (0);
}

static int	init_anal(struct dirent *f, t_iwc *iwc, int *wc, int *i)
{
	if (iwc->nwc == 1 && iwc->wci == 1 && iwc->wcf == 1)
		return (0);
	iwc->p = f->d_name;
	if (iwc->wci && iwc->nwc == 1)
		*wc += 1;
	else if (iwc->nwc > 0)
	{
		if (iwc->wci
			|| !ft_strncmp(iwc->p, iwc->ptrn[*i], ft_strlen(iwc->ptrn[*i])))
		{
			iwc->p = ft_strnstr(iwc->p, iwc->ptrn[*i], ft_strlen(f->d_name));
			if (!iwc->p)
				return (1);
			iwc->p += ft_strlen(iwc->ptrn[(*i)++]);
			if (iwc->wci)
				*wc += 1;
		}
		else
			return (1);
	}
	return (2);
}

static int	anal_f(struct dirent *f, t_iwc *iwc, int wc, int i)
{
	iwc->r = init_anal(f, iwc, &wc, &i);
	if (iwc->r < 2)
		return (iwc->r);
	while (++wc < iwc->nwc)
	{
		if (wc == iwc->nwc - 1)
			continue ;
		iwc->p = ft_strnstr(iwc->p, iwc->ptrn[i], ft_strlen(iwc->p));
		if (!iwc->p)
			return (1);
		iwc->p += ft_strlen(iwc->ptrn[i]);
		if (iwc->ptrn[i + 1] != NULL)
			i++;
	}
	if (iwc->wcf && wc == iwc->nwc)
		return (0);
	else
	{
		if (((int)ft_strlen(f->d_name) - (int)ft_strlen(iwc->ptrn[i])) < 0)
			return (1);
		iwc->p = f->d_name + (ft_strlen(f->d_name) - ft_strlen(iwc->ptrn[i]));
		if (ft_strcmp(iwc->p, iwc->ptrn[i]) == 0)
			return (0);
	}
	return (1);
}

static t_list	*expand_wc(char *s, t_iwc *iwc, t_list *matchs, char *copy)
{
	struct dirent	*f;
	DIR				*dirp;

	dirp = opendir(iwc->path);
	f = readdir(dirp);
	while (f)
	{
		if (iwc->nwc == 0 && !((*f->d_name == '.' && (*s != '.'))
				|| !ft_strcmp(".", f->d_name) || !ft_strcmp("..", f->d_name)))
		{
			if (ft_strcmp(f->d_name, s) == 0)
			{
				copy = ft_strdup(f->d_name);
				ft_lstadd_back(&matchs, ft_lstnew(copy));
			}
		}
		else if (!(*f->d_name == '.' && *s != '.')
			&& (anal_f(f, iwc, -1, 0) != 1))
		{
			copy = ft_strdup(f->d_name);
			ft_lstadd_back(&matchs, ft_lstnew(copy));
		}
		f = readdir(dirp);
	}
	return (closedir(dirp), matchs);
}

t_list	*wildcard_gestor(char *str)
{
	t_iwc	iwc;
	t_list	*matchs;

	if (*str == '\0')
		return (NULL);
	matchs = NULL;
	getcwd(iwc.path, 1024);
	if (creat_iwc(&iwc, str, -1, 0))
		return (NULL);
	matchs = expand_wc(str, &iwc, matchs, NULL);
	ft_free_params(iwc.ptrn);
	return (matchs);
}
