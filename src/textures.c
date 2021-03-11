/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:04:51 by fignigno          #+#    #+#             */
/*   Updated: 2021/01/07 15:55:56 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		open_textures(t_map *map, t_all *all)
{
	int		i;
	void	*img;
	int		tmp[3];

	i = 0;
	while (i < 4)
	{
		all->sizetext[i][0] = 0;
		all->sizetext[i][1] = 0;
		++i;
	}
	i = 0;
	while (i < 4)
	{
		if (!(img = mlx_xpm_file_to_image(all->win.mlx,
		map->texture[i], &((all->sizetext[i])[0]), &((all->sizetext[i])[1]))))
			return (0);
		all->text[i] = (unsigned int *)mlx_get_data_addr(img,
			&tmp[0], &tmp[1], &tmp[2]);
		++i;
		free(img);
	}
	return (1);
}
