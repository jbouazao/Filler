/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:44:17 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/21 10:44:18 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

static void	fill_map(int i, int j, int score, t_map *map)
{
	if ((i - 1 >= 0) && (j - 1 >= 0) && map->map[i - 1][j - 1] == 0)
		map->map[i - 1][j - 1] = (map->map[i][j] == -2) ? 1 : score;
	if ((i - 1 >= 0) && map->map[i - 1][j] == 0)
		map->map[i - 1][j] = (map->map[i][j] == -2) ? 1 : score;
	if ((i - 1 >= 0) && (j + 1 < map->y) && map->map[i - 1][j + 1] == 0)
		map->map[i - 1][j + 1] = (map->map[i][j] == -2) ? 1 : score;
	if ((j - 1 >= 0) && map->map[i][j - 1] == 0)
		map->map[i][j - 1] = (map->map[i][j] == -2) ? 1 : score;
	if ((j - 1 >= 0) && (i + 1 < map->x) && map->map[i + 1][j - 1] == 0)
		map->map[i + 1][j - 1] = (map->map[i][j] == -2) ? 1 : score;
	if ((i + 1 < map->x) && map->map[i + 1][j] == 0)
		map->map[i + 1][j] = (map->map[i][j] == -2) ? 1 : score;
	if ((j + 1 < map->y) && map->map[i][j + 1] == 0)
		map->map[i][j + 1] = (map->map[i][j] == -2) ? 1 : score;
	if ((j + 1 < map->y) && (i + 1 < map->x) && map->map[i + 1][j + 1] == 0)
		map->map[i + 1][j + 1] = (map->map[i][j] == -2) ? 1 : score;
}

void		heat_map_gen(t_map *map)
{
	int score;
	int	target;
	int i;
	int j;
	int k;

	target = -2;
	score = 1;
	k = -1;
	while ((i = -1) && ++k < map->y)
	{
		while ((j = -1) && ++i < map->x)
			while (++j < map->y)
				if (map->map[i][j] == target)
					fill_map(i, j, score, map);
		target = score;
		score++;
	}
}

int			chk_height(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->x)
	{
		j = 0;
		while (j < map->y)
		{
			if (map->map[i][j] == -1 && i > map->x / 3)
				return (1);
			else if (map->map[i][j] == -1 && map->x / 3)
				return (0);
			j++;
		}
		i++;
	}
	return (0);
}

int			chk_len(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->x)
	{
		j = 0;
		while (j < map->y)
		{
			if (map->map[i][j] == -1 && j > map->y / 4)
				return (1);
			else if (map->map[i][j] == -1 && j <= map->y / 4)
				return (0);
			j++;
		}
		i++;
	}
	return (0);
}
