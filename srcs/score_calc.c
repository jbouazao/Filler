/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:47:14 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/28 12:47:15 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

int		get_score(t_map *map, int i, int j, int st)
{
	int k;
	int score;

	k = 0;
	score = 0;
	while (k < map->cnt_str)
	{
		if ((i + map->sc[k][0] - map->sc[st][0] < 0 || i + map->sc[k][0] -
		map->sc[st][0] >= map->x || j + map->sc[k][1] - map->sc[st][1] < 0
		|| j + map->sc[k][1] - map->sc[st][1] >= map->y) && (score = 1000000))
			break ;
		if (k != st && map->map[i + (map->sc[k][0] - map->sc[st][0])][j +
		map->sc[k][1] - map->sc[st][1]] > 0)
			score += map->map[i + (map->sc[k][0] - map->sc[st][0])][j +
			map->sc[k][1] - map->sc[st][1]];
		else if ((k != st && map->map[i + (map->sc[k][0] - map->sc[st][0])][j +
		map->sc[k][1] - map->sc[st][1]] < 0) && (score = 1000000))
			break ;
		k++;
	}
	return (score);
}

void	calc_scores(t_map *map)
{
	int i[3];
	int score;
	int st;

	i[0] = -1;
	map->min_score.s = 100000;
	while (!(score = 0) && ++i[0] < map->x)
	{
		i[1] = -1;
		while (++i[1] < map->y && !(st = 0))
			if (map->map[i[0]][i[1]] == -1 && !(i[2] = 0))
				while (!(score = 0) && i[2] < map->cnt_str)
				{
					score = get_score(map, i[0], i[1], st);
					if (score <= map->min_score.s)
					{
						map->min_score.x = i[0] - map->sc[st][0];
						map->min_score.y = i[1] - map->sc[st][1];
						map->min_score.s = score;
					}
					st++;
					i[2]++;
				}
	}
}
