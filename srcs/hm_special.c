/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 11:13:06 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/28 11:13:07 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"
#include "../get_next_line.h"

void		hm_fill_O(t_P *map)
{
	int i;
	int j;

	i = -1;
	while ((j = -1) && ++i < map->x)
		while (++j < map->y)
			if (map->map[i][j] == 0)
				map->map[i][j] = 100;
}

void		heat_map_i(t_P *map)
{
	int i;
	int j;
	int k;
	int score;
	int flag;

	i = -1;
	while ((j = -1) && ++i < map->x)
	{
		while (!(score = 0) && ++j < map->y)
			if (map->map[i][j] == -1 && (flag = 1))
			{
				while ((k = j) && i >= 0)
				{
					while (k >= 5 && map->map[i][k] != -1 &&
					map->map[i][k] != -2)
						map->map[i][k--] = score;
					i--;
					score++;
				}
				break ;
			}
		i = (flag == 1) ? 1000000 : i;
	}
	hm_fill_O(map);
}

void		heat_map_j2(t_P *map, int i, int j)
{
	int k;
	int score;

	while (i >= 2)
	{
		score = 1;
		k = j;
		while (k >= 0)
		{
			if (map->map[i][k] != -1 && map->map[i][k] != -2)
				map->map[i][k] = score;
			score++;
			k--;
		}
		i--;
	}
}

void		heat_map_j(t_P *map)
{
	int i;
	int j;
	int score;

	i = -1;
	score = 0;
	while (!(j = 0) && ++i < map->x)
	{
		while (j < map->y && map->map[i][j] != -1)
			j++;
		if (map->map[i][j] == -1)
			break ;
	}
	heat_map_j2(map, i, j);
	hm_fill_O(map);
}