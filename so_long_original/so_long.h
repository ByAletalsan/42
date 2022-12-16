/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:27:08 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/15 21:17:39 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct mapa
{
	char	*mapa;
	int		width;
	int		height;
}	t_mapa;

typedef struct player
{
	int	x;
	int	y;
}	t_player;

typedef struct img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct sprites
{
	t_img	floor;
	t_img	wall;
	t_img	door[4]; //marco, fondo, puerta cerrada, puerta abierta
	t_img	chest;
	t_img	player; //21x50
}	t_sprites;

typedef struct game
{
	t_vars		vars;
	t_mapa		map;
	t_player	player;
	t_sprites	spr;
}	t_game;

//Player
int		ft_move_right(t_game *game);
int		ft_move_left(t_game *game);
int		ft_move_top(t_game *game);
int		ft_move_down(t_game *game);
void	ft_find_position_player(t_game *game);
//Map
void	ft_read_map(const char	*s, t_game *game);
int		ft_check_map(const char *s);
int		ft_check_ber(const char *s);
int		ft_check_limit(const char *s);
void	ft_render_map(t_game *game);
//Libft
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_printf(char const *s, ...);
//GET_NEXT_LINE
char	*get_next_line(int fd);

#endif