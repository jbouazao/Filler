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

typedef struct	s_P
{
	int		x;
	int		y;
	char	P;
	int		**map;
	int		p_c[2];
	int		**piece;
	int		cnt_str;
	int		**sc;
}				t_P;

typedef struct	s_score
{
	int x;
	int y;
	int s;
}				t_score;

void	PLMP_init(t_P *P);
void	init_map(t_P *map);
void	print_map(t_P map);
void	heat_map(t_P *map);
void	init_piece(t_P *map);
void	print_piece(t_P map);
void	PP_det(t_P *map, char *line);
void	det_plpo(t_P *map, char *line);
void	get_stars_coord(t_P *map, char *line);
int		ft_strsch(const char *s, char c);
void	free_map(t_P *map);

#endif
