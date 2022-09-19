/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:50:39 by asalas-s          #+#    #+#             */
/*   Updated: 2022/07/26 17:41:16 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

struct s_map
{
	char	**map;
	char	char_empty;
	char	char_obstacle;
	char	char_full;
	int		height;
	int		width;
};

struct s_square
{
	int	x_i;
	int	y_i;
	int	x_f;
	int	y_f;
	int	area;
};

#endif