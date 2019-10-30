/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbouazao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:15:14 by jbouazao          #+#    #+#             */
/*   Updated: 2019/10/21 10:15:16 by jbouazao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "./ft_printfasm/src/ft_printf.h"
# include "get_next_line.h"

typedef struct	s_score
{
	int x;
	int y;
	int s;
}				t_score;

typedef struct	s_map
{
	int				x;
	int				y;
	char			p;
	int				**map;
	int				p_c[2];
	int				**piece;
	int				cnt_str;
	int				**sc;
	struct s_score	min_score;
}				t_map;

void			init_s_score(t_score *score);
void			plmp_init(t_map *p);
int				init_map(t_map *map);
void			print_map(t_map map);
void			heat_map(t_map *map);
void			init_piece(t_map *map);
void			print_piece(t_map map);
int				pp_det(t_map *map, char *line);
void			det_plpo(t_map *map, char *line);
void			get_stars_coord(t_map *map, char *line);
int				fill_score_coord(t_map *map);
int				ft_strsch(const char *s, char c);
void			free_map(t_map *map);
int				get_score(t_map *map, int i, int j, int st);
int				get_piece_dim(t_map *map, char *line);
void			fill_sc(t_map *map);
void			calc_scores(t_map *map);
void			free_piece(t_map *map);
int				record_moves(t_map *map, char *line);
void			free_sc(t_map *map);
void			heat_map_i(t_map *map);
void			heat_map_j(t_map *map);
void			heat_map_gen(t_map *map);
int				chk_height(t_map *map);
int				chk_len(t_map *map);
void			call_gnl_free(int fd, char *line, int count);
void			freeingandall(t_map *map, char **line);
void			free_and_exit(t_map *map);
void			hm_fill_zero(t_map *map);
int				rec_get_pce_cord_fill(t_map *map, char *line);

#endif
