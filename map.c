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

#include "filler.h"
#include "get_next_line.h"

void		PLMP_init(t_P *P)
{
	P->x = 0;
	P->y = 0;
	P->P = 'o';
	P->p_c[0] = 0;
	P->p_c[1] = 0;
	P->cnt_str = 0;
}

void		free_map(t_P *map)
{
	int i;

	i = 0;
	while (i < map->x)
		free(map->map[i++]);
}

void		init_map(t_P *map)
{
	int i;
	int j;

	i = 0;
	map->map = (int **)malloc(sizeof(int *) * map->x);
	while (i < map->x)
	{
		j = 0;
		map->map[i] = (int *)malloc(sizeof(int) * map->y);
		while (j < map->y)
		{
			map->map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void		print_map(t_P map)
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
			if(map.map[i][j+1] > 9 || map.map[i][j+1] < 0)
				ft_putchar_fd(' ', 3);
			else
				ft_putstr_fd("  ", 3);
			j++;
		}
		ft_putendl_fd("", 3);
		i++;
	}
}