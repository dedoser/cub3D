/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:59:05 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/05 15:12:28 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		find_str(char *str, char *p)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*str)
	{
		if (*str == p[i])
		{
			tmp = str;
			while (*tmp == p[i])
			{
				++i;
				++tmp;
			}
			if (!p[i] && *tmp == ' ')
				return (1);
			i = 0;
		}
		++str;
	}
	return (0);
}

char	**copy_map(char **mass, char **res)
{
	int	i;

	i = 8;
	while (mass[i])
	{
		res[i] = mass[i];
		++i;
	}
	res[i] = NULL;
	free(mass);
	return (res);
}

char	**get_order(char **mass, int count)
{
	char	**res;
	int		i;

	if (!(res = (char **)ft_calloc(count + 1, sizeof(char *))))
		return (NULL);
	i = -1;
	while (++i < 8)
		if (find_str(mass[i], "R"))
			res[0] = mass[i];
		else if (find_str(mass[i], "NO"))
			res[1] = mass[i];
		else if (find_str(mass[i], "SO"))
			res[2] = mass[i];
		else if (find_str(mass[i], "WE"))
			res[3] = mass[i];
		else if (find_str(mass[i], "EA"))
			res[4] = mass[i];
		else if (find_str(mass[i], "S"))
			res[5] = mass[i];
		else if (find_str(mass[i], "F"))
			res[6] = mass[i];
		else if (find_str(mass[i], "C"))
			res[7] = mass[i];
	return (copy_map(mass, res));
}
