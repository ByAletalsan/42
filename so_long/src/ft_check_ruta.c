/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ruta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:44:11 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 16:34:58 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//move -> direction: 0 right, 1 bot, 2 left, 3 top

int	ft_check_ruta(t_game game, int x, int y, char *map_cp)
{
	if (x < 0 || x > game.map.width + 1 || y < 0 || y > game.map.height + 1)
		return (1);
	if (map_cp[(y * (game.map.width + 1) + x)] == 'E')
		return (0);
	if (map_cp[(y * (game.map.width + 1) + x)] == '1')
		return (1);
	map_cp[(y * (game.map.width + 1) + x)] = '1';
	if (!ft_check_ruta(game, x + 1, y, map_cp))
		return (0);
	if (!ft_check_ruta(game, x - 1, y, map_cp))
		return (0);
	if (!ft_check_ruta(game, x, y - 1, map_cp))
		return (0);
	if (!ft_check_ruta(game, x, y + 1, map_cp))
		return (0);
	return (1);
}

int	ft_check_cofres(t_game game, int x, int y, char *map_cp)
{
	if (x < 0 || x > game.map.width + 1 || y < 0 || y > game.map.height + 1)
		return (1);
	if (map_cp[(y * (game.map.width + 1) + x)] == 'C')
	{
		game.map.mapa[(y * (game.map.width + 1) + x)] = '0';
		return (0);
	}
	if (map_cp[(y * (game.map.width + 1) + x)] == '1'
		|| map_cp[(y * (game.map.width + 1) + x)] == 'E')
		return (1);
	map_cp[(y * (game.map.width + 1) + x)] = '1';
	if (!ft_check_cofres(game, x + 1, y, map_cp))
		return (0);
	if (!ft_check_cofres(game, x - 1, y, map_cp))
		return (0);
	if (!ft_check_cofres(game, x, y - 1, map_cp))
		return (0);
	if (!ft_check_cofres(game, x, y + 1, map_cp))
		return (0);
	return (1);
}
