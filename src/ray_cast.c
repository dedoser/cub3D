/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:15:26 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 15:55:34 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		det_side(t_cast *cas)
{
	if (cas->side == 1)
	{
		if (cas->raydiry > 0)
			return (1);
		return (0);
	}
	else
	{
		if (cas->raydirx > 0)
			return (3);
		return (2);
	}
}

void	draw_line(t_all *game, t_cast *cas, int x)
{
	int	h;
	int	color;
	int	floor;
	int ceil;

	game->cas = cas;
	h = (int)(game->r_y / cas->walldist);
	cas->line_h = h;
	ceil = game->r_y / 2 - h / 2;
	ceil = ceil * (ceil > 0);
	floor = h / 2 + game->r_y / 2;
	if (floor >= game->r_y)
		floor = game->r_y - 1;
	cas->ceil = ceil;
	cas->floor = floor;
	color = 0x0000FF00;
	if (cas->side)
		color /= 2;
	print_line(&(game->win), create_dip(0, ceil), x, game->info->ceil);
	print_text(&(game->win), x, game);
	print_line(&(game->win), create_dip(floor, game->r_y), x,
				game->info->floor);
}

void	dda(t_all *game, t_cast *cas)
{
	while (!cas->hit)
	{
		if (cas->sidedistx < cas->sidedisty)
		{
			cas->sidedistx += cas->deltadistx;
			cas->mapx += cas->stepx;
			cas->side = 0;
		}
		else
		{
			cas->sidedisty += cas->deltadisty;
			cas->mapy += cas->stepy;
			cas->side = 1;
		}
		if (game->map[cas->mapy][cas->mapx] == '1')
			cas->hit = game->map[cas->mapy][cas->mapx] - '0';
	}
	if (!cas->side)
		cas->walldist = (cas->mapx - game->pl->x + (1 - cas->stepx) / 2)
						/ cas->raydirx;
	else
		cas->walldist = (cas->mapy - game->pl->y + (1 - cas->stepy) / 2)
						/ cas->raydiry;
	if (cas->walldist <= 0)
		cas->walldist = 1;
}

void	wall_hit(t_all *game, t_cast *cas)
{
	cas->deltadistx = (cas->raydiry != 0) *
		((cas->raydirx == 0) ? 1 : fabsf(1 / cas->raydirx));
	cas->deltadisty = (cas->raydirx != 0) *
		((cas->raydiry == 0) ? 1 : fabsf(1 / cas->raydiry));
	if (cas->raydirx < 0)
	{
		cas->stepx = -1;
		cas->sidedistx = (game->pl->x - cas->mapx) * cas->deltadistx;
	}
	else
	{
		cas->stepx = 1;
		cas->sidedistx = (cas->mapx + 1.0f - game->pl->x) * cas->deltadistx;
	}
	if (cas->raydiry < 0)
	{
		cas->stepy = -1;
		cas->sidedisty = (game->pl->y - cas->mapy) * cas->deltadisty;
	}
	else
	{
		cas->stepy = 1;
		cas->sidedisty = (cas->mapy + 1.0f - game->pl->y) * cas->deltadisty;
	}
}

void	ray_cast(t_all *game)
{
	int		i;
	float	camera;
	t_pl	*tmp;
	t_cast	cas;

	i = -1;
	tmp = game->pl;
	while (++i < game->r_x)
	{
		camera = 2 * i / (float)game->r_x - 1;
		cas.raydirx = tmp->dirx + tmp->planex * camera;
		cas.raydiry = tmp->diry + tmp->planey * camera;
		cas.hit = 0;
		cas.mapx = (int)tmp->x;
		cas.mapy = (int)tmp->y;
		wall_hit(game, &cas);
		dda(game, &cas);
		game->z_buff[i] = cas.walldist;
		draw_line(game, &cas, i);
	}
}
