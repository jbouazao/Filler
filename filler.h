#ifndef FILLER_H
# define FILLER_H
# include "./ft_printfasm/src/ft_printf.h"

typedef struct  s_pos
{
	int x;
	int y;
}               t_pos;

typedef struct	s_info
{
	char	player;
	t_pos	board_size;
	t_pos	shape_size;
	t_pos	enemy_pos;
	t_pos	player_pos;
	int		**board;
	int		flag;
}				t_info;

t_info			info_init(void);

#endif