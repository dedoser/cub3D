/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_res.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:47:03 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/20 13:45:34 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		get_resol(t_map *map, char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != 'R')
		return (0);
	i = 0;
	while (!ft_isdigit(str[i]))
		++i;
	map->r_x = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		++i;
	++i;
	map->r_y = ft_atoi(&str[i]);
	return (1);
}

int		get_textures(t_map *map, char **mass)
{
	char	**tmp;
	int		i;
	char	*str;

	str = "NSWE";
	i = 0;
	while (i < 4)
	{
		if (!mass[i])
			return (0);
		tmp = ft_split(mass[i], ' ');
		if (tmp[0][0] != str[i] || !(map->texture[i] = ft_strdup(tmp[1])))
			return (clean_split(tmp));
		++i;
		clean_split(tmp);
	}
	return (1);
}

int		get_sprite(t_map *map, char *str)
{
	char **tmp;

	if (!(tmp = ft_split(str, ' ')))
		return (0);
	map->sprite = ft_strdup(tmp[1]);
	clean_split(tmp);
	return (1);
}

int		get_color(t_map *map, char *str)
{
	char	**mass;
	int		r;
	int		g;
	int		b;
	int		ind;

	if (!str)
		return (0);
	ind = str[0] == 'F';
	while (!ft_isdigit(*str))
		++str;
	if (!(mass = ft_split(str, ',')))
		return (0);
	r = ft_atoi(mass[0]);
	g = ft_atoi(mass[1]);
	b = ft_atoi(mass[2]);
	clean_split(mass);
	if (r < 0 || r > 255 || g < 0 || g > 255 ||
		b < 0 || b > 255)
		return (0);
	if (ind)
		map->floor = r << 16 | g << 8 | b;
	else
		map->ceil = r << 16 | g << 8 | b;
	return (1);
}

t_map	*get_res(char **mass, int count)
{
	t_map	*res;
	int		i;

	if (!(res = (t_map *)ft_calloc(sizeof(t_map), 1)))
		return (NULL);
	if (!get_resol(res, mass[0]) || !get_textures(res, &(mass[1])) ||
		!get_sprite(res, mass[5]) || !get_color(res, mass[6]) ||
		!get_color(res, mass[7]))
	{
		free(res);
		return (NULL);
	}
	i = 8;
	if (!(res->map = (char **)malloc(sizeof(char *) * (count + 1 - 8))))
		return (NULL);
	while (mass[i])
	{
		res->map[i - 8] = ft_strdup(mass[i]);
		++i;
	}
	res->map[i - 8] = NULL;
	clean_split(mass);
	return (res);
}
