/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:12:39 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/04 19:12:42 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

static int is_double_point(t_shape shape, t_point point)
{
	int index;

	index = shape.point_count - 1;
	if (index >= 0)
	{
		if (shape.points[index].x == point.x && shape.points[index].y)
			return TRUE;
	}
	return FALSE;
}

static void    edit_first_shape(t_app *app, t_point point)
{
	int idx;
	int points_count;
	int shapes_count;
	t_shape *shape;

	shape = &app->current_shape;
	shapes_count = app->shapes_count;
	points_count = shape->point_count;
	idx = point_index_of_shapes(shape, point.x, point.y);

	if (idx == -1 && is_line_intersect(shape, point.x, point.y) == FALSE)
	{
		if (points_count == 3)
		{
			add_point_sector(shape, point);
			point.x = shape->points[0].x;
			point.y = shape->points[0].y;
		}

		add_point_sector(shape, point);
		if (points_count >= 3) {
			update_shape_locked_state(shape);
		}
	}
}

static void    edit_next_shape(t_app *app, t_point point)
{
	int idx;
	int points_count;
	int shapes_count;
	t_shape *shape;

	shape = &app->current_shape;
	shapes_count = app->shapes_count;
	points_count = shape->point_count;
	idx = point_index_of_shapes(shape, point.x, point.y);
	printf("HERE 1\n");

	if (idx == -1 && is_line_intersect(shape, point.x, point.y) == FALSE)
	{
		printf("HERE 2\n");

		if (points_count == 0)
		{
			if (is_point_control(app, point.x, point.y) == FALSE)
				return;
		} else {
			if ((points_count == 1 || points_count == 2)) {
				if (is_point_control(app, point.x, point.y) == TRUE) {
					printf("HERE 5\n");
					return;

				}
				if (is_point_intersect_shapes(app, point) == TRUE) {
					printf("HERE 3\n");
					return;
				}
				if (is_line_intersect_shapes(app, shape->points[shape->point_count - 1], point) == TRUE) {
					printf("HERE 4\n");
					return;
				}
			}

			if (points_count == 3) {
				if (is_point_control(app, point.x, point.y) == FALSE) {
					shape->point_count = 0;
					return;
				}
				if (is_line_intersect_shapes(app, shape->points[shape->point_count - 1], point) == TRUE) {
					printf("HERE 6\n");
					return;
				}
				if (is_shapes_has_segment(app, shape->points[0], point) == FALSE)
				{
					shape->point_count = 0;
					return;
				}
			}


		}


//
//        if (points_count > 0 && is_point_intersect_shapes(app, point) == TRUE)
//            return;


		if (points_count == 3)
		{
			add_point_sector(shape, point);
			app->joint_sector = get_line(shape->points[0].x, shape->points[0].y, point.x, point.y);
			app->joint_sector_id = shape->id;
			point.x = shape->points[0].x;
			point.y = shape->points[0].y;
		}

		add_point_sector(shape, point);
		if (points_count >= 3) {
			update_shape_locked_state(shape);
		}

	}


}


void    edit_game_scene(t_app *app, t_point point)
{
	if (app->shapes_count == 0)
		edit_first_shape(app, point);
	else
		edit_next_shape(app, point);

}