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
	int		enemy[2];
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
	P->enemy[0] = 0;
	P->enemy[1] = 0;
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

static void	hm1(t_P *map, int i, int j)
{
	int inc;

	while (i < map->x && (j = map->enemy[1]))
	{
		while (j < map->y && (map->map[i][j] != 0 && map->map[i][j] != -1))
		{
			inc = (map->map[i][j]) + 1;
			if ((j + 1 < map->y) && map->map[i][j + 1] == 0)
				map->map[i][j + 1] = (map->map[i][j] == -2) ? 1 : inc;
			if ((i + 1 < map->x) && map->map[i + 1][j] == 0)
				map->map[i + 1][j] = (map->map[i][j] == -2) ? 1 : inc;
			if ((i + 1 < map->x) && (j + 1 < map->y) &&
			map->map[i + 1][j + 1] == 0)
				map->map[i + 1][j + 1] = (map->map[i][j] == -2) ? 1 : inc;
			j++;
		}
		i++;
	}
}

static void	hm2(t_P *map, int i, int j)
{
	int inc;

	while (i >= 0 && (j = map->enemy[1]))
	{
		while (j >= 0 && (map->map[i][j] != 0 && map->map[i][j] != -1))
		{
			inc = (map->map[i][j]) + 1;
			if ((i - 1 >= 0) && (j - 1 >= 0) && map->map[i - 1][j - 1] == 0)
				map->map[i - 1][j - 1] = (map->map[i][j] == -2) ? 1 : inc;
			if ((i - 1 >= 0) && map->map[i - 1][j] == 0)
				map->map[i - 1][j] = (map->map[i][j] == -2) ? 1 : inc;
			if ((j - 1 >= 0) && map->map[i][j - 1] == 0)
				map->map[i][j - 1] = (map->map[i][j] == -2) ? 1 : inc;
			j--;
		}
		i--;
	}
}

static void	hm3(t_P *map, int i, int j)
{
	int inc;

	while (i >= 0 && (j = map->enemy[1]))
	{
		while (j < map->y && (map->map[i][j] != 0 && map->map[i][j] != -1))
		{
			inc = (map->map[i][j]) + 1;
			if ((i - 1 >= 0) && map->map[i - 1][j] == 0)
				map->map[i - 1][j] = (map->map[i][j] == -2) ? 1 : inc;
			if ((i - 1 >= 0) && (j + 1 < map->y) && map->map[i - 1][j + 1] == 0)
				map->map[i - 1][j + 1] = (map->map[i][j] == -2) ? 1 : inc;
			if ((j + 1 < map->y) && map->map[i][j + 1] == 0)
				map->map[i][j + 1] = (map->map[i][j] == -2) ? 1 : inc;
			j++;
		}
		i--;
	}
}

static void	hm4(t_P *map, int i, int j)
{
	int inc;

	while (i < map->x && (j = map->enemy[1]))
	{
		while (j >= 0 && (map->map[i][j] != 0 && map->map[i][j] != -1))
		{
			inc = (map->map[i][j]) + 1;
			if ((j - 1 >= 0) && map->map[i][j - 1] == 0)
				map->map[i][j - 1] = (map->map[i][j] == -2) ? 1 : inc;
			if ((i + 1 < map->x) && (j - 1 >= 0) && map->map[i + 1][j - 1] == 0)
				map->map[i + 1][j - 1] = (map->map[i][j] == -2) ? 1 : inc;
			if ((i + 1 < map->x) && map->map[i + 1][j] == 0)
				map->map[i + 1][j] = (map->map[i][j] == -2) ? 1 : inc;
			j--;
		}
		i++;
	}
}

void		heat_map(t_P *map, int i, int j)
{
	i = map->enemy[0];
	j = map->enemy[1];
	hm1(map, i, j);
	hm2(map, i, j);
	hm3(map, i, j);
	hm4(map, i, j);
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
		{
			map.map[i][j] = (map.P == 'x') ? -1 : -2;
			map.enemy[0] = (map.map[i][j] == -2) ? i : 0;
			map.enemy[1] = (map.map[i][j] == -2) ? j : 0;
		}
		else if ((j = ft_strsch(line + 4, 'O')) >= 0)
		{
			map.map[i][j] = (map.P == 'o') ? -1 : -2;
			map.enemy[0] = (map.map[i][j] == -2) ? i : 0;
			map.enemy[1] = (map.map[i][j] == -2) ? j : 0;
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
	// ft_putnbr_fd(map.p_c[0], fd);
	// ft_putchar_fd(' ', fd);
	// ft_putnbr_fd(map.p_c[1], fd);
	// ft_putendl_fd("", fd);
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
				star[k++][1] = j;
			}
			j++;
		}
		i++;
	}
	print_piece(map);
	heat_map(&map, i, j);
	i = 0;
	int start = 0;
	int score;
	t_score min_score;
	int l;
	
	score = 0;
	min_score.s = 10000000;
	while (i < map.x)
	{
		j = 0;
		while (j < map.y)
		{
			if (map.map[i][j] == -1)
			{
				l = 0;
				while (l < c_s)
				{
					k = 0;
					while (k < c_s)
					{
						if (k != start && map.map[i + (star[k][0] - star[start][0])][j + star[k][1] - star[start][1]] > 0)
						{
							score += map.map[i + (star[k][0] - star[start][0])][j + star[k][1] - star[start][1]];
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
	ft_printf("%d %d\n", min_score.x, min_score.y);
	// print_map(map);
	// ft_putnbr_fd(map.piece[0], fd);
	// ft_putendl_fd("", fd);
	// ft_putnbr_fd(map.piece[1], fd);
	return (0);
}