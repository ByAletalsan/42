/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:51:34 by atalaver          #+#    #+#             */
/*   Updated: 2023/10/06 14:36:58 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef WIDTH
#  define WIDTH 1080
# endif
# ifndef HEIGHT
#  define HEIGHT 720
# endif
# define SQ 64
# define SM 0.125
# define SPEED 8
# define MPI 3.14159265358979323846
# include <math.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct data_map
{
	char		**map;
	uint32_t	f;
	uint32_t	c;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			pos_x;
	int			pos_y;
	char		orientation;
}	t_data_map;

/*

añadidas mx y my para guardar las coordenadas del mouse

*/

typedef struct player
{
	int		x;
	int		y;
	int32_t	mx;
	int32_t	my;
	double	angle;
	double	fov;
}	t_player;

typedef struct tx
{
	uint8_t		*c;
	uint32_t	color;
	int			i;
	double		y;
	int			contador;
	double		z;
	double		p;
	double		tam;
}	t_tx;

typedef struct any_vars
{
	int		*check;
	int		ctrl;
	int		x;
	int		y;
	double	fx;
	double	fy;
	int		c;
	double	a_r;
}	t_any_vars;

typedef struct textures
{
	mlx_texture_t	*t_we;
	mlx_texture_t	*t_no;
	mlx_texture_t	*t_so;
	mlx_texture_t	*t_ea;
	mlx_texture_t	*t_kick0;
	mlx_texture_t	*t_kick1;
	mlx_image_t		*i_kick;
	mlx_texture_t	*t_door;
}	t_textures;

typedef struct vector
{
	double	dist;
	int		x;
	int		y;
	char	c;
	int		xm;
	int		ym;
}	t_vector;

typedef struct s_vars
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_data_map	*map;
	t_player	player;
	t_any_vars	trash;
	t_textures	tx;
	int			c_k;
	int			fr;
	int			fr_k;
	int			c_d;
	t_vector	*v_d;
}			t_var;

typedef struct point
{
	int	x;
	int	y;
}	t_point;

int			load_textures_map(char *filename, t_data_map *map);
int			load_colors_map(char *filename, t_data_map *map);
int			load_content_map(t_data_map *map, int fd, t_any_vars *av);
void		free_map(t_data_map *map);
int			checkfilename(char *filename);
int			check_ids(int *check, char *id);
uint32_t	get_rgba(int r, int g, int b, int a);
t_data_map	*load_map(char *filename);
int			check_valid_map(t_data_map *map);
void		init_map(t_data_map *map);
t_vector	*rays_vertical(t_var *vars, double angle);
t_vector	*rays_horizontal(t_var *vars, double angle);
int			print_minimap(t_var *v, t_vector *vh, t_vector *vv);
t_vector	*create_vector_horizontal(double ray_x, double ray_y, t_var *vars);
t_vector	*create_vector_vertical(double ray_x, double ray_y, t_var *vars);
void		print_data_map(t_data_map *map);
t_vector	*raycast(t_var *vars, double angle);
void		vector_to_open_door_h(double rx, double ry, t_var *v);
void		vector_to_open_door_v(double rx, double ry, t_var *v);
int			check_limits_rays(double rx, double ry, t_var *v);
void		print_kick(t_var *v);
int			print_textures(t_var *v, t_vector *vh, t_vector *vv);
void		print_background(t_var *vars);
void		print_texture_so(t_var *v, t_vector *vc,
				double x_print, double tam);
void		print_texture_no(t_var *v, t_vector *vc,
				double x_print, double tam);
void		print_texture_we(t_var *v, t_vector *vc,
				double x_print, double tam);
void		print_texture_ea(t_var *v, t_vector *vc,
				double x_print, double tam);
void		print_texture_door_v(t_var *v, t_vector *vc,
				double x_print, double tam);
void		print_texture_door_h(t_var *v, t_vector *vc,
				double x_print, double tam);
int			valid_location(t_var *vars, char key);
void		hook_camera(t_var *vars);
void		hook_mouse(t_var *vars);
void		hook_kick(t_var *va, t_vector *v);
void		hooks_wasd(t_var *vars);
void		load_player(t_var *vars);
void		free_data(t_var *vars);
int			load_textures(t_var *vars);

#endif
