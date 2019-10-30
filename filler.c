/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:21:16 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/21 10:21:17 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "get_next_line.h"

int	rec_get_pce_cord_fill(t_map *map, char *line)
{
	if (!(record_moves(map, line)))
		return (1);
	get_piece_dim(map, line);
	get_stars_coord(map, line);
	fill_score_coord(map);
	return (0);
}

int	main()
{
	char	*line;
	t_map	map;

	line = NULL;
	plmp_init(&map);
	if (!(pp_det(&map, line)))
		return (1);
	while (1)
	{
		if (rec_get_pce_cord_fill(&map, line))
			return (1);
		if (map.p == 'x' && map.x == 15 && map.y == 17 && chk_height(&map))
			heat_map_i(&map);
		else if (map.p == 'x' && map.x == 15 && map.y == 17 && chk_len(&map))
			heat_map_j(&map);
		else
			heat_map_gen(&map);
		calc_scores(&map);
		ft_printf("%d %d\n", map.min_score.x, map.min_score.y);
		freeingandall(&map, &line);
	}
	free_map(&map);
	return (0);
}
