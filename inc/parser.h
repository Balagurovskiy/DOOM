/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:09:11 by obalagur          #+#    #+#             */
/*   Updated: 2019/06/01 12:11:30 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "doom.h"

# define BUFF_SIZE 100
# define HAS_N (after_n = ft_strchr(*line, '\n')) != NULL

int					get_next_line(const int fd, char **line);
void				*for_each_gnl(char *file, void *(*f)(char *, int));

# define TO_FLOAT(x) (float)x * 1.0

typedef	struct		s_map_vertex
{
	int						neighbor;
	float					x;
	float					y;

	struct s_map_vertex		*next;
}					t_map_vertex;

typedef	struct		s_map_sector
{
	t_map_vertex			*vertex;
	int						vertex_size;

	int						floor;
	int						ceil;

	char					*next_level;
	int						next_level_sector;

	t_map_vertex			*object;

	struct s_map_sector		*next;
}					t_map_sector;

typedef	struct		s_map
{
	t_map_sector	*sector;
	int				sector_size;

	char			*floortexture;
	char			*ceiltexture;
	char			*uppertextures;
	char			*lowertextures;
}					t_map;

t_map_vertex		*map_new_vertex();
void				map_add_vertex(t_map_vertex **first, t_map_vertex *new);
void				map_del_vertex(t_map_vertex **node);

t_map_sector		*map_new_sector();
void				map_add_sector(t_map_sector **first, t_map_sector *new);
void				map_del_sector(t_map_sector **node);

char				*str_cut(char *line, int start, int end);
char				*cut_str_value(char *line, char *start, char *end);
void				loop_str_to_value(char **line,
										char *value, int condition);
int					char_isdigit(int c);
int					str_isdigit(char *s);

void				free_splinter(char **splt, int size);
int					parse_atoi(char *str);
int					parse_singe_value(char **line, char *flag, char *separ);
int					iterate(int max);
int					catch_exception(int status);

void				parse_vertex_switch(t_map_vertex *vertex,
										char *str, int condition);
void				parse_vertex(char **vertex,
						t_map_vertex **fvertex, int *count, int *size);
t_map_vertex		*parse_sector(char **line, int *count);
t_map_vertex		*parse_sector_object(char **line);

char				*parse_level(char **line, int *nxt_sector);
void				parse_level_info(char **lvl_info,
								int *it, char **nxt_lvl, int *nxt_sctr);

void				parse_line(char **line, t_map_sector **map_sector);
t_map				*parser(char *line, int status);

t_player			init_player(float a,
							t_sectors *s, unsigned int s_in, int num_s);

void				set_sector_object(t_sectors *s, t_map_sector *ms);

void				sector_validation(t_level lvl);

t_texture_set		connect_textures(t_map *map);
t_sectors			*connect_sectors(t_map *map);

void				connect_next_level(t_level *lvl, t_map *map);

t_map				*get_map(char *file_name);
t_level				connect_level(t_map *map);

void				parse_texture_switch(char **txt_data,
										t_map **map, int *it);
void				parse_texture(char *line, t_map **map);

# define VRTX(s, v) lvl.sector[s].vertex[v]

#endif
