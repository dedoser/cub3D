/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:47:20 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/20 13:13:04 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdio.h>

# define PI 3.141592653
# define SIZE 10
# define STEP 0.007
# define ROT 0.03 * PI
# define PLANE PI/4
# define H	20
# define SM	0.08
# define SR	0.06

# define ARGS "Error - not enough arguments\n"
# define WR_FL "Error - can't read file\n"
# define NOT_V "Error - not valid map\n"
# define ALLOC "Allocation error\n"
# define WR_ARGS "Error - wrong arguments\n"

typedef struct	s_map
{
	int		r_x;
	int		r_y;
	char	*texture[4];
	char	*sprite;
	int		floor;
	int		ceil;
	char	**map;
	int		count;
	int		max_len;
	int		spr_count;
}				t_map;

typedef struct	s_pl {
	float	x;
	float	y;
	float	angle;
	float	start;
	float	end;
	float	dirx;
	float	diry;
	float	planex;
	float	planey;
}				t_pl;

typedef struct	s_win {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_win;

typedef struct	s_cast
{
	float	raydirx;
	float	raydiry;
	int		mapx;
	int		mapy;
	float	sidedistx;
	float	sidedisty;
	float	deltadistx;
	float	deltadisty;
	float	walldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	float	wallx;
	int		line_h;
	int		ceil;
	int		floor;
}				t_cast;

typedef struct	s_spr
{
	float	spr_x;
	float	spr_y;
	float	invdet;
	float	trans_x;
	float	trans_y;
	int		spr_screen_x;
	int		spr_height;
	int		spr_wid;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
}				t_spr;

typedef struct	s_sprite
{
	double	x;
	double	y;
}				t_sprite;

typedef struct	s_all {
	t_pl		*pl;
	t_win		win;
	t_map		*info;
	t_cast		*cas;
	char		**map;
	int			r_x;
	int			r_y;
	void		*text[4];
	int			sizetext[4][2];
	void		*spr;
	int			sizespr[2];
	double		*z_buff;
	t_sprite	*sprites;
	int			spr_count;
	int			save;
}				t_all;

int				clean_split(char **mass);
void			clean_mass(char **mass, int count);
int				clean_map(t_map *map, int num);
int				clean_t_map(t_map *map);
int				clean_game(t_all *all, t_map *map);
char			**get_order(char **mass, int count);
t_map			*reader(char *name);
t_map			*get_res(char **mass, int count);
int				key_arrows(int keycode, t_all *g);
int				valid_map(t_map *map);
t_pl			*find_pl(char **mass);
void			print_square(t_win *img, int x, int y, int color);
void			print_line(t_win *img, int *se, int x, int color);
int				*create_dip(int a, int b);
void			ray_cast(t_all *game);
void			draw_map_play(t_all *all);
void			my_mlx_pixel_put(t_win *data, int x, int y, int color);
int				open_textures(t_map *map, t_all *all);
int				det_side(t_cast *cas);
void			print_text(t_win *img, int x, t_all *al);
int				open_sprite(t_all *all);
int				add_sprite(t_all *all);
void			draw_sprite(t_all *all);
void			put_sprite(t_all *all, t_spr *spr, int *tex, int *i);
void			sort_sprites(t_pl *pl, t_sprite *mass, int count);
int				create_image(t_all *all);
void			print_error(char *str);
int				map_start(char *str);
int				add_line(char **mass, char *str, int *i, int *map_b);
int				add_line2(char *str, int map_b);
int				check_res(t_all *game);
int				check_file_name(char *str);
int				close_window(int keycode);
int				check_content(char **map);
#endif
