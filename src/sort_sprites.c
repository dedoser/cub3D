/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:04:17 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 15:56:05 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	swap(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_sprites(t_pl *pl, t_sprite *mass, int count)
{
	float		d1;
	float		d2;
	int			ind;
	int			i;

	ind = 1;
	while (ind)
	{
		ind = 0;
		i = 0;
		while (i < count - 1)
		{
			d1 = ((pl->x - mass[i].x) * (pl->x - mass[i].x) +
					(pl->y - mass[i].y) * (pl->y - mass[i].y));
			d2 = ((pl->x - mass[i + 1].x) * (pl->x - mass[i + 1].x) +
					(pl->y - mass[i + 1].y) * (pl->y - mass[i + 1].y));
			if (d1 < d2)
			{
				swap(&mass[i], &mass[i + 1]);
				ind = 1;
			}
			++i;
		}
	}
}

void	put_sprite(t_all *all, t_spr *spr, int *tex, int *i)
{
	int				d;
	unsigned int	color;

	d = i[1] * 256 - all->r_y * 128 + spr->spr_height * 128;
	tex[1] = ((d * all->sizespr[1]) / spr->spr_height) / 256;
	color = ((unsigned int *)(all->spr))[all->sizespr[0] * tex[1] + tex[0]];
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&all->win, spr->draw_start_x, i[1], color);
}
