/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:57:55 by ahmansou          #+#    #+#             */
/*   Updated: 2019/07/13 19:09:07 by ahmansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../libft/libft.h"

typedef struct	s_types
{
	char		types[11];
	void		(*t[11])(const char *frm, va_list ap, int *i, int *sz);
}				t_types;

typedef	struct s_flags
{
	int	mi;
	int plus; // '+' = +; '-' = -
	int space;
	int zero;
	int wd;
	int pr;
	int dot;
	int h; //0 1 2
	int l; //0 1 2
	int oc;
}				t_flags;

t_types	get_types();

int				ft_printf(const char *format, ...);
void			get_params(const char *frm, va_list ap, int *i, int *sz);
void    		c_proc(const char *frm, va_list ap, int *i, int *sz);
void    		s_proc(const char *frm, va_list ap, int *i, int *sz);
void    		d_proc(const char *frm, va_list ap, int *i, int *sz);
void    		o_proc(const char *frm, va_list ap, int *i, int *sz);
void			u_proc(const char *frm, va_list ap, int *i, int *sz);
void			x_proc(const char *frm, va_list ap, int *i, int *sz);
void			p_proc(const char *frm, va_list ap, int *i, int *sz);
void			get_flgs(const char *frm, t_flags *flgs, int *i, char c);
int				put_space(int sp_sz);
int				n_len(long long n);
int				put_zero(int z_sz);
long	long	get_va_arg(va_list ap, t_flags flgs);
unsigned long long get_va_arg_o(va_list ap, t_flags flgs);
char			*itoa_base(unsigned long long nbr, int base);