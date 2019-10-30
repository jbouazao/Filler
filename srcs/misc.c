/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:31:15 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/21 10:31:17 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../filler.h"

int		ft_strsch(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-3);
}

void	init_s_score(t_score *score)
{
	score->s = 0;
	score->x = 0;
	score->y = 0;
}

void	plmp_init(t_map *map)
{
	map->x = 0;
	map->y = 0;
	map->p = 'o';
	map->p_c[0] = 0;
	map->p_c[1] = 0;
	map->cnt_str = 0;
}
