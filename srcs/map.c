/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:20:55 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/21 10:20:56 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

int		init_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	if (!(map->map = (int **)ft_memalloc(sizeof(int *) * map->x)))
		return (0);
	while (i < map->x)
	{
		j = 0;
		map->map[i] = (int *)ft_memalloc(sizeof(int) * map->y);
		while (j < map->y)
		{
			map->map[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}

int		record_moves(t_map *map, char *line)
{
	int i;
	int j;

	i = -1;
	while (++i < map->x)
	{
		j = 0;
		if (!(get_next_line(0, &line)))
		{
			free_map(map);
			return (0);
		}
		while (j < map->y)
		{
			if (line[j + 4] == 'X' || line[j + 4] == 'x')
				map->map[i][j] = (map->p == 'x') ? -1 : -2;
			else if (line[j + 4] == 'O' || line[j + 4] == 'o')
				map->map[i][j] = (map->p == 'o') ? -1 : -2;
			else
				map->map[i][j] = 0;
			j++;
		}
		ft_strdel(&line);
	}
	return (1);
}

void	print_map(t_map map)
{
	int i;
	int j;

	i = 0;
	while (i < map.x)
	{
		j = 0;
		while (j < map.y)
		{
			ft_putnbr_fd(map.map[i][j], 3);
			if (map.map[i][j + 1] > 9 || map.map[i][j + 1] < 0)
				ft_putchar_fd(' ', 3);
			else
				ft_putstr_fd("  ", 3);
			j++;
		}
		ft_putendl_fd("", 3);
		i++;
	}
	ft_putendl_fd("", 3);
}

int		pp_det(t_map *map, char *line)
{
	int i;

	i = 0;
	if (get_next_line(0, &line) < 0)
		return (0);
	if (ft_strstr(line, "p2"))
		map->p = 'x';
	ft_strdel(&line);
	if (get_next_line(0, &line) < 0)
		return (0);
	if (ft_strstr(line, "Plateau"))
	{
		map->x = ft_atoi(line + 8);
		while (line[i + 8] != ' ')
			i++;
		map->y = ft_atoi(line + 8 + i);
		ft_strdel(&line);
		if (!(init_map(map)))
			return (0);
		call_gnl_free(0, line, 1);
	}
	return (1);
}
