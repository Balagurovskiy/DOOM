/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scaler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/02 12:46:26 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "doom.h"
#include "render_scaler.h"

t_scaler_set	set_scaler(int a, int b, int c)
{
	t_scaler_set	ss;

	ss.a = a;
	ss.b = b;
	ss.c = c;
	return (ss);
}

t_scaler		scaler_init(t_scaler_set ss, int d, int f)
{
	t_scaler	s;
	int			c_a;

	c_a = ((ss.c - ss.a) == 0) ? 1 : (ss.c - ss.a);
	s.result = d + (ss.b - 1 - ss.a) * (f - d) / c_a;
	s.bop = ((f < d) ^ (ss.c < ss.a)) ? -1 : 1;
	s.fd = ABS(f - d);
	s.ca = ABS(ss.c - ss.a);
	s.cache = (int)((ss.b - 1 - ss.a) * ABS(f - d)) % ABS(c_a);
	return (s);
}

int				scaler_next(t_scaler *s)
{
	s->cache += s->fd;
	while (s->cache >= s->ca)
	{
		s->result += s->bop;
		s->cache -= s->ca;
	}
	return (s->result);
}
