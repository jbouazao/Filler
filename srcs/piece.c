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

#include "../filler.h"
#include "../get_next_line.h"

void	free_piece(t_P *map)
{
	int i;

	i = 0;
	while (i < map->p_c[0])
	{
		free(map->piece[i]);
		map->piece[i++] = NULL;
	}
	free(map->piece);
	map->piece = NULL;
}

void	print_piece(t_P map)
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

int		get_piece_dim(t_P *map, char *line)
{
	int i;

	i = 0;
	if (get_next_line(0, &line) < 0)
		return (0);
	if (ft_strstr(line, "Piece"))
	{
		map->p_c[0] = ft_atoi(line + 6);
		while (line[i + 6] != ' ')
			i++;
		map->p_c[1] = ft_atoi(line + i + 6);
	}
	ft_strdel(&line);
	if (!(map->piece = (int **)ft_memalloc(sizeof(int *) * map->p_c[0])))
		return (0);
	i = 0;
	while (i < map->p_c[0])
		map->piece[i++] = (int *)ft_memalloc(sizeof(int) * map->p_c[1]);
	return (1);
}

void	get_stars_coord(t_P *map, char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	map->cnt_str = 0;
	while (!(j = 0) && i < map->p_c[0])
	{
		if (get_next_line(0, &line) >= 0)
		{
			while (j < map->p_c[1])
			{
				if (line[j] == '.')
					map->piece[i][j++] = 0;
				else if (line[j] == '*')
				{
					map->piece[i][j++] = -1;
					map->cnt_str++;
				}
			}
			ft_strdel(&line);
		}
		i++;
	}
}

int		fill_score_coord(t_P *map)
{
	int i;
	int j;
	int k;

	if (!(map->sc = (int **)ft_memalloc(sizeof(int *) * map->cnt_str)))
		return (0);
	else
	{
		i = 0;
		while (i < map->cnt_str)
			map->sc[i++] = (int *)ft_memalloc(sizeof(int) * 2);
		i = 0;
		k = 0;
		while (i < map->p_c[0])
		{
			j = 0;
			while (j < map->p_c[1])
			{
				if (map->piece[i][j] == -1)
				{
					map->sc[k][0] = i;
					map->sc[k][1] = j;
					k++;
				}
				j++;
			}
			i++;
		}
	}
	return (1);
}