/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_operator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:35:27 by atalaver          #+#    #+#             */
/*   Updated: 2023/06/26 16:35:28 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_skip_other_tk(char *cmd, int *idx, char find)
{
	int	i;

	i = *idx - 1;
	while (i > 0)
	{
		if (cmd[i] == find && cmd[i - 1] == '\\')
			i--;
		else if (cmd[i] == find)
			break ;
		else
			i--;
	}
	if (i == 0 && cmd[i] != find)
		printf("No matching token was found for %c\n", find);
	*idx = i - 1;
}

void	ft_count_next_par(char *cmd, int *idx, int *pars_cnt)
{
	int	i;

	i = *idx;
	while (i > 0)
	{
		if (cmd[i] == '(' || cmd[i] == ')')
		{
			if (cmd[i - 1] == '\\')
				i--;
			else
				break ;
		}
		else if (cmd[i] == '\'' || cmd[i] == '"')
			ft_skip_other_tk(cmd, &i, cmd[i]);
		else
			i--;
	}
	if (cmd[i] == '(')
		(*pars_cnt)--;
	else if (cmd[i] == ')')
		(*pars_cnt)++;
	*idx = i - 1;
}

void	ft_skip_par(char *cmd, int *idx)
{
	int	i;	
	int	pars_cnt;	

	i = *idx;
	if (cmd[i] != ')')
		return ;
	i--;
	pars_cnt = 1;
	while (i >= 0)
	{
		ft_count_next_par(cmd, &i, &pars_cnt);
		if (pars_cnt == 0)
			break ;
	}
	if (pars_cnt != 0)
		printf("Parenthesis mismatch!\n");
	*idx = i;
}

int	ft_is_token(char c)
{
	return (c == '(' || c == ')' || c == '\'' || c == '"');
}

void	ft_skip_token(char *cmd, int *idx)
{
	char	tk;

	tk = cmd[*idx];
	if (tk == ')')
		ft_skip_par(cmd, idx);
	else
		ft_skip_other_tk(cmd, idx, tk);
}
