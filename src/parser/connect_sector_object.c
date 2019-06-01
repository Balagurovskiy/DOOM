/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_sector_object.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:36:49 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:40:49 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		add_error(float *a, float *b, int doit, int sign)
{
	if (doit)
	{
		if (sign > 0)
		{
			(*a) += 0.1;
			(*b) += 0.1;
		}
		else
		{
			(*a) -= 0.1;
			(*b) -= 0.1;
		}
		return (1);
	}
	return (0);
}

void	correction(sectors *s)
{
	xy	*obj0;
	xy	*obj1;

	obj0 = &(s->object_xy[0]);
	obj1 = &(s->object_xy[1]);
	if (add_error(&(obj0->y), &(obj1->y), (obj0->x > obj1->x), -1))
		return ;
	if (add_error(&(obj0->y), &(obj1->y), (obj0->x < obj1->x), 1))
		return ;
	if (add_error(&(obj0->x), &(obj1->x), (obj0->y > obj1->y), 1))
		return ;
	if (add_error(&(obj0->x), &(obj1->x), (obj0->y < obj1->y), -1))
		return ;
}

void	set_sector_object(sectors *s, t_map_sector *ms)
{
	t_map_vertex	*mso;
	int				i;

	s->object = 0;
	if (ms->object == NULL)
		return ;
	i = 0;
	mso = ms->object;
	while (mso)
	{
		if (i < 2)
		{
			s->object_xy[i].x = mso->x;
			s->object_xy[i].y = mso->y;
			s->object = mso->neighbor;
		}
		mso = mso->next;
		i++;
	}
	correction(s);
}
