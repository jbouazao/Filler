/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:05 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/21 10:28:06 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "get_next_line.h"

void	init_piece(t_P *map)
{
	int i;

	i = 0;
	map->piece = (int **)malloc(sizeof(int *) * map->p_c[0]);
	while (i < map->p_c[0])
		map->piece[i++] = (int *)malloc(sizeof(int) * map->p_c[1]);
}

void		print_piece(t_P map)
{
	int i;
	int j;

	i = 0;
	while (i < map.p_c[0])
	{
		j = 0;
		while (j < map.p_c[1])
		{
			ft_putnbr_fd(map.piece[i][j], 3);
			ft_putchar_fd(' ', 3);
			j++;
		}
		ft_putendl_fd("", 3);
		i++;
	}
}