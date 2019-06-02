/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scaler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:42 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_SCALER_H
# define RENDER_SCALER_H

typedef struct	s_scaler_set
{
	int	a;
	int	b;
	int	c;
}				t_scaler_set;

typedef struct	s_scaler
{
	int	result;
	int	bop;
	int	fd;
	int	ca;
	int	cache;
}				t_scaler;

t_scaler_set	set_scaler(int a, int b, int c);
t_scaler		scaler_init(t_scaler_set ss, int d, int f);
int				scaler_next(t_scaler *s);

#endif
