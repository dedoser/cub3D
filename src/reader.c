/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:37:00 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/20 13:58:17 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	**read_file(int fd, int count)
{
	char	*line;
	char	**res;
	int		i;
	int		ind;
	int		map_b;

	if (!(res = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	i = 0;
	map_b = 0;
	while ((ind = get_next_line(fd, &line)) > 0)
	{
		if (!add_line(res, line, &i, &map_b))
			return (NULL);
		if (add_line2(line, map_b))
			continue ;
	}
	free(line);
	if (ind < 0)
	{
		clean_mass(res, i);
		return (NULL);
	}
	res[i] = NULL;
	return (res);
}

int		count_str(char *name)
{
	char	c;
	int		count;
	int		fd;
	int		len;

	count = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		return (-1);
	len = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
		{
			count += (len > 0);
			len = 0;
		}
		else
			++len;
	}
	close(fd);
	return (count);
}

t_map	*read_res(int fd, int count)
{
	char	**mass;

	if (!(mass = read_file(fd, count)))
		return (NULL);
	return (get_res(get_order(mass, count), count));
}

int		find_max_len(char **mass)
{
	int	i;
	int	max;
	int	tmp;

	i = 0;
	max = 0;
	while (mass[i])
	{
		tmp = ft_strlen(mass[i]);
		if (max < tmp)
			max = tmp;
		++i;
	}
	return (max);
}

t_map	*reader(char *name)
{
	t_map	*res;
	int		fd;
	int		count;

	if (!check_file_name(name) ||
		(count = count_str(name)) < 0)
	{
		print_error(WR_FL);
		exit(0);
	}
	else if ((fd = open(name, O_RDONLY)) < 0)
	{
		print_error(WR_FL);
		exit(0);
	}
	else if (!(res = read_res(fd, count)))
		res = NULL;
	close(fd);
	if (res)
	{
		res->max_len = find_max_len(res->map);
		res->count = count - 8;
	}
	return (res);
}
