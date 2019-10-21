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

void	PP_det(t_P *map, char *line)
{
	int i;

	i = 0;
	get_next_line(0, &line);
	if (ft_strstr(line, "p2"))
		map->P = 'x';
	free(line);
	get_next_line(0, &line);
	if (ft_strstr(line, "Plateau"))
	{
		map->x = ft_atoi(line + 8);
		while (line[i + 8] != ' ')
			i++;
		map->y = ft_atoi(line + 8 + i);
		free(line);
		init_map(map);
		get_next_line(0, &line);
	}
	free(line);
}

void	get_piece_dim(t_P *map, char *line)
{
	int i;

	i = 0;
	get_next_line(0, &line);
	if (ft_strstr(line, "Piece"))
	{
		map->p_c[0] = ft_atoi(line + 6);
		while (line[i + 6] != ' ')
			i++;
		map->p_c[1] = ft_atoi(line + i + 6);
	}
	free(line);
}

void	det_plpo(t_P *map, char *line)
{
	int i;
	int j;

	i = 0;
	while (i < map->x)
	{
		get_next_line(0, &line);
		if ((j = ft_strsch(line + 4, 'X')) >= 0)
			map->map[i][j] = (map->P == 'x') ? -1 : -2;
		else if ((j = ft_strsch(line + 4, 'O')) >= 0)
			map->map[i][j] = (map->P == 'o') ? -1 : -2;
		free(line);
		i++;
	}
}

void	get_stars_coord(t_P *map, char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (!(j = 0) && i < map->p_c[0])
	{
		get_next_line(0, &line);
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
		free(line);
		i++;
	}
	map->sc = (int **)malloc(sizeof(int *) * map->cnt_str + (i = 0));
	while (i < map->cnt_str)
		map->sc[i++] = (int *)malloc(sizeof(int) * 2);
}

void	fill_sc(t_P *map)
{
	int i;
	int j;
	int k;

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

int main ()
{
	char	*line;
	t_P		map;
	int		i;
	int		j;
	int		k;
	t_score	min_score;

	line = NULL;
	i = 0;
	k = 0;
	PLMP_init(&map);
	PP_det(&map, line);
	det_plpo(&map, line);
	get_piece_dim(&map, line);
	init_piece(&map);
	get_stars_coord(&map, line);
	fill_sc(&map);
	heat_map(&map);
	//----------------------------
	//----------------------------
	i = 0;
	int st = 0;
	int score;
	int l;
	
	score = 0;
	min_score.s = 100000;
	while (i < map.x)
	{
		j = 0;
		while (j < map.y)
		{
			if (map.map[i][j] == -1)
			{
				l = 0;
				st = 0;
				while (l < map.cnt_str)
				{
					k = 0;
					while (k < map.cnt_str)
					{
						if (i + map.sc[k][0] - map.sc[st][0] < 0 || i + map.sc[k][0] - map.sc[st][0] >= map.x
						|| j + map.sc[k][1] - map.sc[st][1] < 0 || j + map.sc[k][1] - map.sc[st][1] >= map.y)
						{
							score = 1000000;
							break ;
						}
						if (k != st && map.map[i + (map.sc[k][0] - map.sc[st][0])][j + map.sc[k][1] - map.sc[st][1]] > 0)
							score += map.map[i + (map.sc[k][0] - map.sc[st][0])][j + map.sc[k][1] - map.sc[st][1]];
						else if (k != st && map.map[i + (map.sc[k][0] - map.sc[st][0])][j + map.sc[k][1] - map.sc[st][1]] < 0)
						{
							score = 1000000;
							break ;
						}
						k++;
					}
					if (score <= min_score.s)
					{
						min_score.x = i - map.sc[st][0];
						min_score.y = j - map.sc[st][1];
						min_score.s = score;
					}
					score = 0;
					st++;
					l++;
				}
			}
			j++;
		}
		i++;
	}
	print_map(map);
	ft_printf("%d %d\n", min_score.x, min_score.y);
	//------------------------------------
	while (1)
	{
		get_next_line(0, &line);
		get_next_line(0, &line);
		i = 0;
		while (i < map.x)
		{
			get_next_line(0, &line);
			j = 0;
			while (j < map.y)
			{
				if (line[j + 4] == 'X' || line[j + 4] == 'x')
					map.map[i][j] = (map.P == 'x') ? -1 : -2;
				else if (line[j + 4] == 'O' || line[j + 4] == 'o')
					map.map[i][j] = (map.P == 'o') ? -1 : -2;
				else
					map.map[i][j] = 0;
				j++;
			}
			i++;
		}
		get_next_line(0, &line);
		if (ft_strstr(line, "Piece"))
		{
			map.p_c[0] = ft_atoi(line + 6);
			while (*(line + 6) != ' ')
				line++;
			map.p_c[1] = ft_atoi(line + 6);
		}
		init_piece(&map);
		i = 0;
		j = 0;
		map.cnt_str = 0;
		while (i < map.p_c[0])
		{
			get_next_line(0, &line);
			j = 0;
			while (j < map.p_c[1])
			{
				if (line[j] == '.')
					map.piece[i][j] = 0;
				else if (line[j] == '*')
				{
					map.piece[i][j] = -1;
					map.cnt_str++;
				}
				j++;
			}
			i++;
		}
		map.sc = (int **)malloc(sizeof(int *) * map.cnt_str);
		i = 0;
		k = 0;
		while (i < map.cnt_str)
			map.sc[i++] = (int *)malloc(sizeof(int) * 2);
		i = 0;
		while (i < map.p_c[0])
		{
			j = 0;
			while (j < map.p_c[1])
			{
				if (map.piece[i][j] == -1)
				{
					map.sc[k][0] = i;
					map.sc[k][1] = j;
					// ft_putnbr_fd(map.sc[k][0], 1);
					// ft_putchar_fd(' ', 1);
					// ft_putnbr_fd(map.sc[k][1], 1);
					// ft_putendl_fd("", 1);
					k++;
				}
				j++;
			}
			i++;
		}
		//ft_putendl_fd("", fd);
		heat_map(&map);
		//print_map(map);
		//---------------------------------------------
		i = 0;
		score = 0;
		min_score.s = 100000;
		st = 0;
		while (i < map.x)
		{
			j = 0;
			while (j < map.y)
			{
				if (map.map[i][j] == -1)
				{
					l = 0;
					st = 0;
					while (l < map.cnt_str)
					{
						k = 0;
						while (k < map.cnt_str)
						{
							if (i + map.sc[k][0] - map.sc[st][0] < 0 || i + map.sc[k][0] - map.sc[st][0] >= map.x
							|| j + map.sc[k][1] - map.sc[st][1] < 0 || j + map.sc[k][1] - map.sc[st][1] >= map.y)
							{
								score = 1000000;
								break ;
							}
							if (k != st && map.map[i + (map.sc[k][0] - map.sc[st][0])][j + (map.sc[k][1] - map.sc[st][1])] >= 0)
								score += map.map[i + (map.sc[k][0] - map.sc[st][0])][j + map.sc[k][1] - map.sc[st][1]];
							else if (k != st && map.map[i + (map.sc[k][0] - map.sc[st][0])][j + map.sc[k][1] - map.sc[st][1]] < 0)
							{
								score = 1000000;
								break ;
							}
							k++;
						}
						if (score < min_score.s /*&& (score > map.cnt_str || score == 0)*/)
						{
							min_score.x = i - map.sc[st][0];
							min_score.y = j - map.sc[st][1];
							min_score.s = score;
						}
						/*else if (score < min_score.s)
						{
							min_score.x = i - map.sc[st][0];
							min_score.y = j - map.sc[st][1];
							min_score.s = score;
						}*/
						score = 0;
						st++;
						l++;
					}
				}
				j++;
			}
			i++;
		}
		ft_printf("%d %d\n", min_score.x, min_score.y);
	}
	// print_map(map);
	// ft_putnbr_fd(map.piece[0], fd);
	// ft_putendl_fd("", fd);
	// ft_putnbr_fd(map.piece[1], fd);
	return (0);
}
