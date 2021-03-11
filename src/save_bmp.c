/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:22:52 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/04 19:21:22 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	put_header(int fd, t_all *all)
{
	char	c;
	int		size;

	c = 'B';
	write(fd, &c, 1);
	c = 'M';
	write(fd, &c, 1);
	size = all->r_y * all->r_x * 4 + 54;
	write(fd, &size, sizeof(size));
	size = (unsigned int)0;
	write(fd, &size, sizeof(size));
	size = 54;
	write(fd, &size, sizeof(size));
}

void	put_info(int fd, t_all *all)
{
	unsigned int	size;
	int				i;

	size = 40;
	write(fd, &size, sizeof(size));
	write(fd, &all->r_x, sizeof(all->r_x));
	write(fd, &all->r_y, sizeof(all->r_y));
	size = 1;
	write(fd, &size, 2);
	size = 32;
	write(fd, &size, 2);
	i = -1;
	size = 0;
	while (++i < 6)
		write(fd, &size, sizeof(int));
}

void	put_body(int fd, t_all *all)
{
	int				i;
	int				j;
	unsigned int	*tmp;

	i = (all->r_y - 1) * all->r_x;
	tmp = (unsigned int *)all->win.addr;
	while (i >= 0)
	{
		j = 0;
		while (j < all->r_x)
		{
			write(fd, &tmp[i], sizeof(unsigned int));
			++j;
			++i;
		}
		i -= 2 * all->r_x;
	}
}

int		create_image(t_all *all)
{
	int		fd;

	fd = open("map.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	put_header(fd, all);
	put_info(fd, all);
	put_body(fd, all);
	return (0);
}
