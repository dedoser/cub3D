/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   description.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 21:25:28 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 15:56:05 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	put_dir(char c, t_pl *res)
{
	if (c == 'N')
	{
		res->angle = PI * 1.5f;
		res->dirx = 0;
		res->diry = -1;
	}
	else if (c == 'W')
	{
		res->angle = PI;
		res->dirx = -1;
		res->diry = 0;
	}
	else if (c == 'S')
	{
		res->angle = PI / 2;
		res->dirx = 0;
		res->diry = 1;
	}
	else if (c == 'E')
	{
		res->angle = 0;
		res->dirx = 1;
		res->diry = 0;
	}
}

void	count_plane(char c, t_pl *pl)
{
	if (c == 'N')
	{
		pl->planex = 0.66f;
		pl->planey = 0.0f;
		return ;
	}
	else if (c == 'S')
	{
		pl->planex = -0.66f;
		pl->planey = 0.0f;
		return ;
	}
	else if (c == 'E')
	{
		pl->planex = 0.0f;
		pl->planey = 0.66f;
		return ;
	}
	pl->planex = 0.0f;
	pl->planey = -0.66f;
}

int		check_letter(char c, int *j)
{
	int	res;

	res = (c == 'S' || c == 'W' || c == 'N' || c == 'E');
	if (!res)
		(*j)++;
	return (res);
}

t_pl	*find_pl(char **mass)
{
	int		i;
	int		j;
	t_pl	*res;

	i = -1;
	while (mass[++i])
	{
		j = 0;
		while (mass[i][j])
		{
			if (ft_isdigit(mass[i][j]) || mass[i][j] == ' ')
				++j;
			else if (check_letter(mass[i][j], &j))
			{
				res = (t_pl *)malloc(sizeof(t_pl));
				res->x = j + 0.1;
				res->y = i + 0.1;
				put_dir(mass[i][j], res);
				count_plane(mass[i][j], res);
				mass[i][j] = '0';
				return (res);
			}
		}
	}
	return (NULL);
}

int		check_res(t_all *game)
{
	int	x;
	int	y;
	int	i;

	mlx_get_screen_size(game->win.mlx, &x, &y);
	if (game->r_x > x || game->r_y > y)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (game->r_x <= game->sizetext[i][0] ||
			game->r_y <= game->sizetext[i][1])
			return (0);
		++i;
	}
	if (game->r_x <= game->sizespr[0] ||
		game->r_y <= game->sizespr[1])
		return (0);
	return (1);
}
