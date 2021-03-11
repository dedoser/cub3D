/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 15:54:50 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 15:56:05 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		count_sprite(t_all *all)
{
	int	i;
	int	j;
	int	res;

	i = -1;
	res = 0;
	while (++i < all->info->count)
	{
		j = -1;
		while (all->map[i][++j])
			res += all->map[i][j] == '2';
	}
	return (res);
}

int		add_sprite(t_all *all)
{
	int	i;
	int	j;
	int	cur;

	i = -1;
	cur = 0;
	all->spr_count = count_sprite(all);
	if (!(all->sprites = (t_sprite *)malloc(sizeof(t_sprite) * all->spr_count)))
		return (0);
	while (++i < all->info->count)
	{
		j = -1;
		while (all->map[i][++j])
		{
			if (all->map[i][j] == '2')
			{
				all->sprites[cur].x = j + 0.4;
				all->sprites[cur].y = i + 0.2;
				++cur;
			}
		}
	}
	return (1);
}

int		open_sprite(t_all *all)
{
	void	*img;
	int		tmp[3];

	if (!(img = mlx_xpm_file_to_image(all->win.mlx, all->info->sprite,
			&(all->sizespr[0]), &(all->sizespr[1]))))
		return (0);
	all->spr = mlx_get_data_addr(img, &tmp[0], &tmp[1], &tmp[2]);
	free(img);
	return (1);
}

void	calc_spr(t_all *all, t_spr *spr, int i, t_pl *pl)
{
	spr->spr_x = all->sprites[i].x - pl->x;
	spr->spr_y = all->sprites[i].y - pl->y;
	spr->invdet = 1.0 / (pl->planex * pl->diry - pl->dirx * pl->planey);
	spr->trans_x = spr->invdet * (pl->diry * spr->spr_x -
				pl->dirx * spr->spr_y);
	spr->trans_y = spr->invdet * (-pl->planey * spr->spr_x +
				pl->planex * spr->spr_y);
	spr->spr_screen_x = (int)((all->r_x / 2) *
				(1 + spr->trans_x / spr->trans_y));
	spr->spr_height = abs((int)(all->r_y / spr->trans_y));
	spr->draw_start_y = -spr->spr_height / 2 + all->r_y / 2;
	spr->draw_start_y *= (spr->draw_start_y > 0);
	spr->draw_end_y = spr->spr_height / 2 + all->r_y / 2;
	if (spr->draw_end_y >= all->r_y)
		spr->draw_end_y = all->r_y - 1;
	spr->spr_wid = abs((int)(all->r_y / spr->trans_y));
	spr->draw_start_x = -spr->spr_wid / 2 + spr->spr_screen_x;
	spr->draw_start_x *= (spr->draw_start_x > 0);
	spr->draw_end_x = spr->spr_wid / 2 + spr->spr_screen_x;
	if (spr->draw_end_x >= all->r_x)
		spr->draw_end_x = all->r_x - 1;
}

void	draw_sprite(t_all *all)
{
	t_spr	spr;
	int		i[2];
	int		tex[2];

	i[0] = -1;
	sort_sprites(all->pl, all->sprites, all->spr_count);
	while (i[0] < all->spr_count)
	{
		calc_spr(all, &spr, i[0], all->pl);
		while (spr.draw_start_x < spr.draw_end_x)
		{
			tex[0] = (int)(256 * (spr.draw_start_x - (-spr.spr_wid / 2 +
			spr.spr_screen_x)) * all->sizespr[0] / spr.spr_wid) / 256;
			i[1] = spr.draw_start_y;
			if (spr.trans_y > 0 && spr.draw_start_x > 0 &&
	spr.draw_start_x < all->r_x && spr.trans_y < all->z_buff[spr.draw_start_x])
				while (i[1] < spr.draw_end_y)
				{
					put_sprite(all, &spr, tex, i);
					++i[1];
				}
			++spr.draw_start_x;
		}
		++i[0];
	}
}
