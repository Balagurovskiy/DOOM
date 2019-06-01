/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:38:57 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:43:13 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		vertex_validation(level_s lvl, int nsctr, int sctr, int vrtxs)
{
	int	nvrtx;
	int	next_vrtx;
	int	eq1;
	int	eq2;

	next_vrtx = vrtxs + 1;
	if (next_vrtx >= lvl.sector[sctr].npoints)
		next_vrtx = 0;
	eq1 = 0;
	eq2 = 0;
	nvrtx = lvl.sector[nsctr].npoints;
	while (nvrtx-- && nvrtx >= 0)
	{
		if (equals_xy(VRTX(sctr, vrtxs), VRTX(nsctr, nvrtx)))
			eq1 = 1;
		if (equals_xy(VRTX(sctr, next_vrtx), VRTX(nsctr, nvrtx)))
			eq2 = 1;
	}
	if (eq1 && eq2)
		return (1);
	return (0);
}

static void		neighbor_validation(level_s lvl, int sctr, int vrtxs)
{
	int	nsctr;

	nsctr = lvl.sector[sctr].neighbors[vrtxs];
	if (nsctr < 0)
		return ;
	if (nsctr >= lvl.sectors_size)
	{
		ft_putstr("EXCEPTION > sector > neighbor sector out of range\n");
		catch_exception(1);
	}
	else
	{
		if (!vertex_validation(lvl, nsctr, sctr, vrtxs))
		{
			ft_putstr("EXCEPTION > vertex > neighbors not synhronized\n");
			catch_exception(1);
		}
	}
}

static void		data_validation(level_s lvl, int sctr, int vrtxs)
{
	int	excptn;
	int	i;

	excptn = 0;
	if (lvl.sector[sctr].ceil < 0 || lvl.sector[sctr].ceil > 50)
		excptn = 1;
	if (lvl.sector[sctr].floor < 0 || lvl.sector[sctr].floor > 50)
		excptn = 2;
	if (VRTX(sctr, vrtxs).x < 0.0 || VRTX(sctr, vrtxs).x > 50.0)
		excptn = 3;
	if (VRTX(sctr, vrtxs).y < 0.0 || VRTX(sctr, vrtxs).y > 50.0)
		excptn = 4;
	i = 3;
	while (i-- && !excptn)
		if ((lvl.start[i] < 0 || lvl.start[i] > 33) && lvl.next_level[i])
			excptn = 6;
	if (excptn)
	{
		ft_putstr("EXCEPTION > sector > invalid data\n");
		catch_exception(1);
	}
}

void			sector_validation(level_s lvl)
{
	int sctr;
	int vrtxs;

	sctr = lvl.sectors_size;
	if (sctr < 1 || sctr > 33)
	{
		ft_putstr("EXCEPTION > sector > invalid sector number\n");
		catch_exception(1);
	}
	while (sctr--)
	{
		vrtxs = lvl.sector[sctr].npoints;
		if (vrtxs < 3 || vrtxs > 10)
		{
			ft_putstr("EXCEPTION > sector > invalid vertex number\n");
			catch_exception(1);
		}
		while (vrtxs--)
		{
			data_validation(lvl, sctr, vrtxs);
			neighbor_validation(lvl, sctr, vrtxs);
			if (catch_exception(0))
				return ;
		}
	}
}
