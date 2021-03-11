/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:05:36 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 17:52:22 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../cub.h"

void	lib_init(t_all *game)
{
	game->win.mlx = mlx_init();
	game->win.win = mlx_new_window(game->win.mlx, game->r_x, game->r_y, "cub");
	game->win.img = mlx_new_image(game->win.mlx, game->r_x, game->r_y);
	game->win.addr = mlx_get_data_addr(game->win.img, &game->win.bits_per_pixel,
				&game->win.line_length, &game->win.endian);
}

int		check_content(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' &&
				map[i][j] != 'N' && map[i][j] != 'W' &&
				map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != '2')
				return (0);
			++j;
		}
		++i;
	}
	return (1);
}

int		configure(t_all *game, t_map *res)
{
	game->r_x = res->r_x;
	game->r_y = res->r_y;
	if (!(game->z_buff = (double *)malloc(sizeof(double) * res->r_x)))
	{
		print_error(ALLOC);
		return (clean_t_map(res));
	}
	game->map = res->map;
	game->info = res;
	lib_init(game);
	if (!check_content(res->map) ||
		!(game->pl = find_pl(res->map)) || !open_textures(res, game)
		|| !open_sprite(game) || !check_res(game))
	{
		print_error(NOT_V);
		return (clean_game(game, res));
	}
	add_sprite(game);
	draw_map_play(game);
	mlx_hook(game->win.win, 2, 1L << 0, key_arrows, game);
	mlx_hook(game->win.win, 17, 1L << 0, close_window, game);
	mlx_loop(game->win.mlx);
	return (0);
}

void	launch(t_all *game, t_map *res, char *name)
{
	if (!(res = reader(name)))
	{
		print_error(NOT_V);
		return ;
	}
	if (!valid_map(res))
	{
		clean_t_map(res);
		print_error(NOT_V);
		return ;
	}
	configure(game, res);
}

int		main(int argc, char **argv)
{
	t_map	*res;
	t_all	game;
	int		i;

	if (argc < 2 || argc > 3)
	{
		print_error(WR_ARGS);
		return (0);
	}
	i = 1;
	if (argc == 3 && !ft_strncmp(argv[1], "--save", 6))
	{
		++i;
		game.save = i == 2;
	}
	else if (argc == 3)
	{
		print_error(WR_ARGS);
		return (0);
	}
	res = NULL;
	launch(&game, res, argv[i]);
	return (0);
}
