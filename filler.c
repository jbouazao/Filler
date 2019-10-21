#include "filler.h"
#include "get_next_line.h"

typedef struct	s_P
{
	int		x;
	int		y;
	char	P;
	int		**map;
	int		p_c[2];
	int		**piece;
}				t_P;

typedef struct	s_score
{
	int x;
	int y;
	int s;
}				t_score;

void	dim_init(t_P *P)
{
	P->x = 0;
	P->y = 0;
	P->P = 'o';
	P->p_c[0] = 0;
	P->p_c[1] = 0;
}

void	init_map(t_P *map)
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

void	print_map(t_P map)
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

void	fill_map(int i, int j, int score, t_P *map)
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

void		heat_map(t_P *map)
{
	int score;
	int	target;
	int i;
	int j;
	int k;

	target = -2;
	score = 1;
	k = -1;
	while (++k < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			j = -1;
			while (++j < map->y)
			{
				if (map->map[i][j] == target)
					fill_map(i, j, score, map);
			}
		}
		target = score;
		score++;
	}
}

int main ()
{
	int		fd;
	char	*line;
	t_P		map;
	int		i;
	int		c_s;
	int		**star;

	i = 0;
	dim_init(&map);
	fd = open("text", O_WRONLY);
	get_next_line(0, &line);
	if (ft_strstr(line, "p2"))
		map.P = 'x';
	get_next_line(0, &line);
	if (ft_strstr(line, "Plateau"))
	{
		map.x = ft_atoi(line + 8);
		while (*(line + 8) != ' ')
			line++;
		map.y = ft_atoi(line + 8);
		init_map(&map);
		get_next_line(0, &line);
	}
	int		j;

	j = 0;
	while (i < map.x)
	{
		get_next_line(0, &line);
		if ((j = ft_strsch(line + 4, 'X')) >= 0)
			map.map[i][j] = (map.P == 'x') ? -1 : -2;
		else if ((j = ft_strsch(line + 4, 'O')) >= 0)
			map.map[i][j] = (map.P == 'o') ? -1 : -2;
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
	c_s = 0;
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
				c_s++;
			}
			j++;
		}
		i++;
	}
	star = (int **)malloc(sizeof(int *) * c_s);
	i = 0;
	int k;

	k = 0;
	while (i < c_s)
		star[i++] = (int *)malloc(sizeof(int) * 2);
	i = 0;
	while (i < map.p_c[0])
	{
		j = 0;
		while (j < map.p_c[1])
		{
			if (map.piece[i][j] == -1)
			{
				star[k][0] = i;
				star[k][1] = j;
				k++;
			}
			j++;
		}
		i++;
	}
	// print_piece(map);
	heat_map(&map);
	i = 0;
	int start = 0;
	int score;
	t_score min_score;
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
				start = 0;
				while (l < c_s)
				{
					k = 0;
					while (k < c_s)
					{
						if (i + star[k][0] - star[start][0] < 0 || i + star[k][0] - star[start][0] >= map.x
						|| j + star[k][1] - star[start][1] < 0 || j + star[k][1] - star[start][1] >= map.y)
						{
							score = 1000000;
							break ;
						}
						if (k != start && map.map[i + (star[k][0] - star[start][0])][j + star[k][1] - star[start][1]] > 0)
							score += map.map[i + (star[k][0] - star[start][0])][j + star[k][1] - star[start][1]];
						else if (k != start && map.map[i + (star[k][0] - star[start][0])][j + star[k][1] - star[start][1]] < 0)
						{
							score = 1000000;
							break ;
						}
						k++;
					}
					if (score < min_score.s)
					{
						min_score.x = i - star[start][0];
						min_score.y = j - star[start][1];
						min_score.s = score;
					}
					score = 0;
					start++;
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
				{
					map.map[i][j] = (map.P == 'x') ? -1 : -2;
					// map.enemy[0] = (map.map[i][j] == -2) ? i : 0;
					// map.enemy[1] = (map.map[i][j] == -2) ? j : 0;
				}
				else if (line[j + 4] == 'O' || line[j + 4] == 'o')
				{
					map.map[i][j] = (map.P == 'o') ? -1 : -2;
					// map.enemy[0] = (map.map[i][j] == -2) ? i : 0;
					// map.enemy[1] = (map.map[i][j] == -2) ? j : 0;
				}
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
		c_s = 0;
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
					c_s++;
				}
				j++;
			}
			i++;
		}
		star = (int **)malloc(sizeof(int *) * c_s);
		i = 0;
		k = 0;
		while (i < c_s)
			star[i++] = (int *)malloc(sizeof(int) * 2);
		i = 0;
		while (i < map.p_c[0])
		{
			j = 0;
			while (j < map.p_c[1])
			{
				if (map.piece[i][j] == -1)
				{
					star[k][0] = i;
					star[k][1] = j;
					// ft_putnbr_fd(star[k][0], 1);
					// ft_putchar_fd(' ', 1);
					// ft_putnbr_fd(star[k][1], 1);
					// ft_putendl_fd("", 1);
					k++;
				}
				j++;
			}
			i++;
		}
		ft_putendl_fd("", fd);
		heat_map(&map);
		print_map(map);
		//---------------------------------------------
		i = 0;
		score = 0;
		min_score.s = 100000;
		start = 0;
		while (i < map.x)
		{
			j = 0;
			while (j < map.y)
			{
				if (map.map[i][j] == -1)
				{
					l = 0;
					start = 0;
					while (l < c_s)
					{
						k = 0;
						while (k < c_s)
						{
							if (i + star[k][0] - star[start][0] < 0 || i + star[k][0] - star[start][0] >= map.x
							|| j + star[k][1] - star[start][1] < 0 || j + star[k][1] - star[start][1] >= map.y)
							{
								score = 1000000;
								break ;
							}
							if (k != start && map.map[i + (star[k][0] - star[start][0])][j + (star[k][1] - star[start][1])] >= 0)
								score += map.map[i + (star[k][0] - star[start][0])][j + star[k][1] - star[start][1]];
							else if (k != start && map.map[i + (star[k][0] - star[start][0])][j + star[k][1] - star[start][1]] < 0)
							{
								score = 1000000;
								break ;
							}
							k++;
						}
						if (score < min_score.s && (score > (c_s - 1) || score == 0))
						{
							min_score.x = i - star[start][0];
							min_score.y = j - star[start][1];
							min_score.s = score;
						}
						/*else if (score < min_score.s)
						{
							min_score.x = i - star[start][0];
							min_score.y = j - star[start][1];
							min_score.s = score;
						}*/
						score = 0;
						start++;
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