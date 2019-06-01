/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:44:48 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:50:37 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

static xy	find_midd_point(sectors sct)
{
	xy		start;
	int		i;

	i = 0;
	start = new_xy(0.0, 0.0);
	while (i < sct.npoints)
	{
		start.x += sct.vertex[i].x;
		start.y += sct.vertex[i].y;
		i++;
	}
	start.x /= i;
	start.y /= i;
	return (start);
}

player	init_player(float a, sectors *s, unsigned int s_in, int num_s)
{
	player	player;
	xy		where;

	where = find_midd_point(s[s_in]);
	player.sector = s_in;
	player.where.x = where.x;
	player.where.y = where.y;
	player.where.z = s[player.sector].floor + EYE_HEIGHT;
	player.velocity.x = 0;
	player.velocity.y = 0;
	player.velocity.z = 0;
	player.angle = a;
	player.anglesin = sinf(player.angle);
	player.anglecos = cosf(player.angle);
	player.yaw = 0;
	player.total_sectors = num_s;
	player.exit_doom = 0;
	player.action = 0;
	player.key = 0;
    return (player);
}