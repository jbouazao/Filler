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
#include "../get_next_line.h"

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

void		PLMP_init(t_P *P)
{
	P->x = 0;
	P->y = 0;
	P->P = 'o';
	P->p_c[0] = 0;
	P->p_c[1] = 0;
	P->cnt_str = 0;
}