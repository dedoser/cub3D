/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:18:48 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 17:49:01 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		check_move(char **map, float x, float y)
{
	if (map[(int)(y)][(int)(x)] == '1')
		return (0);
	return (1);
}

void	change_angle(t_pl *g, int ind)
{
	float	olddirx;
	float	oldplanex;

	olddirx = g->dirx;
	g->dirx = g->dirx * cos(ind * SR) - g->diry * sin(ind * SR);
	g->diry = olddirx * sin(ind * SR) + g->diry * cos(ind * SR);
	oldplanex = g->planex;
	g->planex = g->planex * cos(ind * SR) - g->planey * sin(ind * SR);
	g->planey = oldplanex * sin(ind * SR) + g->planey * cos(ind * SR);
}

void	ws_move(int keycode, t_all *g)
{
	if (keycode == 13)
	{
		if (g->map[(int)g->pl->y][(int)(g->pl->x + g->pl->dirx * SM)] == '0')
			g->pl->x += g->pl->dirx * SM;
		if (g->map[(int)(g->pl->y + g->pl->diry * SM)][(int)(g->pl->x)] == '0')
			g->pl->y += g->pl->diry * SM;
	}
	else if (keycode == 1)
	{
		if (g->map[(int)g->pl->y][(int)(g->pl->x - g->pl->dirx * SM)] == '0')
			g->pl->x -= g->pl->dirx * SM;
		if (g->map[(int)(g->pl->y - g->pl->diry * SM)][(int)(g->pl->x)] == '0')
			g->pl->y -= g->pl->diry * SM;
	}
}

void	ad_move(int keycode, t_all *g)
{
	if (keycode == 2)
	{
		if (g->map[(int)g->pl->y][(int)(g->pl->x + g->pl->planex * SM)] == '0')
			g->pl->x += g->pl->planex * SM;
		if (g->map[(int)(g->pl->y + g->pl->planey * SM)][(int)(g->pl->x)]
			== '0')
			g->pl->y += g->pl->planey * SM;
	}
	if (keycode == 0)
	{
		if (g->map[(int)g->pl->y][(int)(g->pl->x - g->pl->planex * SM)] == '0')
			g->pl->x -= g->pl->planex * SM;
		if (g->map[(int)(g->pl->y - g->pl->planey * SM)][(int)(g->pl->x)]
			== '0')
			g->pl->y -= g->pl->planey * SM;
	}
}

int		key_arrows(int keycode, t_all *g)
{
	if (keycode == 53)
	{
		mlx_destroy_window(g->win.mlx, g->win.win);
		clean_game(g, g->info);
	}
	ws_move(keycode, g);
	ad_move(keycode, g);
	if (keycode == 123)
		change_angle(g->pl, -1);
	else if (keycode == 124)
		change_angle(g->pl, 1);
	draw_map_play(g);
	return (keycode);
}
