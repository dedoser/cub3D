/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:31:01 by walker            #+#    #+#             */
/*   Updated: 2021/01/20 13:46:30 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*add_spaces(char *str, int count)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (count + 1));
	i = -1;
	while (str[++i])
		res[i] = str[i];
	while (i < count)
	{
		res[i] = ' ';
		++i;
	}
	res[i] = '\0';
	free(str);
	return (res);
}

void	equal_len(char **mass, int max_len)
{
	int	i;
	int	size;

	i = 0;
	while (mass[i])
	{
		size = max_len - ft_strlen(mass[i]);
		if (size)
			mass[i] = add_spaces(mass[i], max_len);
		++i;
	}
}

int		lr_cover(char *str)
{
	int		j;

	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] == ' ')
			++j;
		if (!str[j])
			break ;
		if (str[j] && str[j] != '1')
			return (0);
		while (str[j] && str[j] != ' ')
			++j;
		if (str[j - 1] != '1')
			return (0);
	}
	return (1);
}

int		ud_cover(char **str, int i)
{
	int		j;

	j = 0;
	while (str[j])
	{
		while (str[j] && str[j][i] == ' ')
			++j;
		if (!str[j])
			break ;
		if (str[j] && str[j][i] != '1')
			return (0);
		while (str[j] && str[j][i] != ' ')
			++j;
		if (str[j - 1][i] != '1')
			return (0);
	}
	return (1);
}

int		valid_map(t_map *map)
{
	int	i;
	int	j;

	if (map->r_x <= 65 || map->r_y <= 65)
		return (0);
	equal_len(map->map, map->max_len);
	i = -1;
	j = -1;
	if (map->map[0] == NULL)
		return (0);
	while (map->map[++i])
		if (!lr_cover(map->map[i]))
			return (0);
	while (map->map[0][++j])
		if (!ud_cover(map->map, j))
			return (0);
	return (1);
}
