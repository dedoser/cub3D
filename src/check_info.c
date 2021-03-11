/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:10:12 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/06 20:57:51 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		check_info(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->texture[i] == NULL)
			return (0);
		++i;
	}
	return (1);
}

int		map_start(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0')
			return (0);
		++i;
	}
	return (i != 0);
}

int		add_line(char **mass, char *str, int *i, int *map_b)
{
	if (!*map_b)
		*map_b = map_start(str);
	if (!*map_b && !ft_strlen(str))
		return (1);
	if (*map_b && !ft_strlen(str))
	{
		clean_mass(mass, *i);
		return (0);
	}
	mass[*i] = str;
	++(*i);
	return (1);
}

int		add_line2(char *str, int map_b)
{
	if (!map_b && !ft_strlen(str))
	{
		free(str);
		return (1);
	}
	return (0);
}

int		check_file_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '.')
		++i;
	++i;
	if (!ft_strncmp(&str[i], "cub", 3))
		return (1);
	return (0);
}
