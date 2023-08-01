/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:30:07 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/26 18:01:10 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	ft_check_left_rigth(int i, char *cmd)
{
	int	j;

	j = i + 1;
	while (cmd[j] && ft_isspace(cmd[j]))
		j++;
	if (cmd[j] == ')' || cmd[j] == '&' || cmd[j] == '|')
		return (1);
	j = i - 2;
	while (j > 0 && ft_isspace(cmd[j]))
		j--;
	if (j <= 0 || cmd[j] == '(' || cmd[j] == '&' || cmd[j] == '|')
		return (1);
	return (0);
}
