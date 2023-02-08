/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:27:08 by atalaver          #+#    #+#             */
/*   Updated: 2023/02/08 20:24:43 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define VEL 4

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
	t_img	door[4];
	t_img	chest;
	t_img	player[4];
	t_img	enemi[4];
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
	int			keys[4];
	int			move;
	int			frame_enemi;
}	t_game;

//Collision
void	ft_rem_obj(t_game *game, t_obj *obj);
//Player
void	ft_move(t_game *game, int x, int y);
t_obj	*ft_find_player(t_list *list);
t_obj	*ft_can_move(t_list *list, int x, int y);
//Map
int		ft_read_map(const char	*s, t_game *game);
int		ft_check_map(t_game game);
int		ft_check_ber(const char *s);
int		ft_check_limit(t_mapa map);
int		ft_check_ruta(t_game game, int x, int y, char *map_cp);
int		ft_check_cofres(t_game game, int x, int y, char *map_cp);
void	ft_render_map(t_game *game);
void	ft_reset_frames(t_game *game);
void	ft_load(t_game *game);
int		ft_free_game(t_game *game);
void	ft_free_obj(t_game *game);
//GET_NEXT_LINE
char	*get_next_line(int fd);
//libft
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*ft_strdup(const char *s);

#endif
