/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:57:12 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 15:55:56 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		*create_dip(int a, int b)
{
	int		*mass;

	mass = (int *)malloc(sizeof(int) * 2);
	mass[0] = a;
	mass[1] = b;
	return (mass);
}

void	print_line(t_win *img, int *se, int x, int color)
{
	while (se[0] < se[1])
	{
		my_mlx_pixel_put(img, x, se[0], color);
		se[0]++;
	}
	if (se)
		free(se);
}

void	print_square(t_win *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			++j;
		}
		++i;
	}
}

void	side(t_all *al)
{
	t_cast	*cas;

	cas = al->cas;
	if (!cas->side)
		cas->wallx = al->pl->y + cas->walldist * cas->raydiry;
	else
		cas->wallx = al->pl->x + cas->walldist * cas->raydirx;
}

void	print_text(t_win *img, int x, t_all *al)
{
	int		i;
	t_cast	*cas;
	int		tex[2];
	float	step;
	float	texpos;

	cas = al->cas;
	i = det_side(cas);
	side(al);
	cas->wallx -= floor(cas->wallx);
	tex[0] = (int)(cas->wallx * (float)(al->sizetext[i][0]));
	if ((!cas->side && cas->raydirx > 0) || (cas->side && cas->raydiry < 0))
		tex[0] = al->sizetext[i][0] - tex[0] - 1;
	step = 1.0 * al->sizetext[i][1] / cas->line_h;
	texpos = (cas->ceil - al->r_y / 2 + cas->line_h / 2) * step;
	tex[0] = al->sizetext[i][0] - tex[0];
	while (cas->ceil < cas->floor)
	{
		tex[1] = (int)texpos & (al->sizetext[i][1] - 1);
		texpos += step;
		my_mlx_pixel_put(img, x, cas->ceil,
			((int **)(al->text))[i][al->sizetext[i][0] * tex[1] + tex[0]]);
		cas->ceil++;
	}
}
