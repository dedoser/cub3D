/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:39:31 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 17:15:56 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clean_screan(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < all->r_y)
	{
		i = 0;
		while (i < all->r_x)
		{
			my_mlx_pixel_put(&(all->win), i, j, 0x00000000);
			++i;
		}
		++j;
	}
}

void	print_2dmap(t_all *game, char **map)
{
	int i;
	int j;
	int color;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				color = 0x00FFFFFF;
			else if (map[i][j] == '2')
				color = 0x0000FFFF;
			else
				color = 0;
			print_square(&(game->win), j * SIZE, i * SIZE, color);
			++j;
		}
		++i;
	}
	print_square(&(game->win), (int)(game->pl->x * SIZE - SIZE / 2),
				(int)(game->pl->y * SIZE - SIZE / 2), 0x0000FF00);
}

void	draw_map_play(t_all *all)
{
	if (all->info->count * SIZE >= all->r_y ||
		all->info->max_len * SIZE >= all->r_x ||
		!check_content(all->map))
	{
		print_error(NOT_V);
		clean_game(all, all->info);
		exit(0);
	}
	clean_screan(all);
	ray_cast(all);
	draw_sprite(all);
	if (all->save)
	{
		create_image(all);
		clean_game(all, all->info);
		exit(0);
	}
	print_2dmap(all, all->map);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
}

int		close_window(int keycode)
{
	exit(0);
	return (keycode);
}
