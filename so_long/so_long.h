/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:27:08 by atalaver          #+#    #+#             */
/*   Updated: 2022/12/20 19:20:50 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define VEL 2

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
	t_img	player[4];
}	t_sprites;

typedef struct obj
{
	char	c;
	int		x;
	int		y;
}	t_obj;

typedef struct game
{
	t_vars		vars;
	t_mapa		map;
	t_sprites	spr;
	t_list		*obj;
	int			frame;
	int			score;
	int			steps;
	int			direction;
	int			pasos;
}	t_game;

//Collision
void	ft_rem_obj(t_game *game, t_obj *obj);
//Player
int		ft_move_right(t_game *game);
int		ft_move_left(t_game *game);
int		ft_move_top(t_game *game);
int		ft_move_down(t_game *game);
//Map
void	ft_read_map(const char	*s, t_game *game);
int		ft_check_map(t_game game);
int		ft_check_ber(const char *s);
int		ft_check_limit(t_mapa map);
void	ft_render_map(t_game *game);
void	ft_load_sprites(t_game *game);
void	ft_free_sprites(t_game *game);
void	ft_print_border(t_game *game);
void	ft_print_obj(t_game *game);
//GET_NEXT_LINE
char	*get_next_line(int fd);

#endif