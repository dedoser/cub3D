/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:52:10 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/06 21:00:13 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		clean_split(char **mass)
{
	int	i;

	i = 0;
	while (mass[i])
	{
		free(mass[i]);
		++i;
	}
	free(mass);
	return (0);
}

void	clean_mass(char **mass, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(mass[i]);
		++i;
	}
	free(mass);
}

int		clean_map(t_map *map, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		free(map->map[i]);
	free(map->map);
	return (0);
}

int		clean_t_map(t_map *map)
{
	int i;

	free(map->sprite);
	i = 0;
	while (i < 4)
	{
		free(map->texture[i]);
		++i;
	}
	clean_map(map, map->count);
	free(map);
	return (0);
}

int		clean_game(t_all *all, t_map *map)
{
	clean_t_map(map);
	if (all->pl)
		free(all->pl);
	exit(0);
	return (0);
}
