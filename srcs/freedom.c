/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 09:35:16 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/29 09:35:17 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

void	free_sc(t_map *map)
{
	int i;

	i = 0;
	while (i < map->cnt_str)
	{
		free(map->sc[i]);
		map->sc[i++] = NULL;
	}
	free(map->sc);
	map->sc = NULL;
}

void	call_gnl_free(int fd, char *line, int count)
{
	while (count--)
	{
		if ((get_next_line(fd, &line)))
			free(line);
	}
}

void	freeingandall(t_map *map, char **line)
{
	free_piece(map);
	free_sc(map);
	call_gnl_free(0, *line, 2);
}

void	free_and_exit(t_map *map)
{
	free_piece(map);
	free_sc(map);
	free_map(map);
}

void	free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->x)
		ft_memdel((void *)&map->map[i++]);
	ft_memdel((void **)&map->map);
}
