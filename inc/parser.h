/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obalagur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:52:40 by obalagur          #+#    #+#             */
/*   Updated: 2018/06/22 11:52:46 by obalagur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "doom.h"

# define BUFF_SIZE 100
# define HAS_N (after_n = ft_strchr(*line, '\n')) != NULL

int		get_next_line(const int fd, char **line);
void	*for_each_gnl(char *file, void *(*f)(char *, int));

//typedef struct		s_list
//{
//    void			*content;
//    size_t			content_size;
//    struct s_list	*next;
//}					t_list;
//
//char				*ft_strchr(const char *s, int c);
//void				ft_strdel(char **as);
//char				*ft_strdup(const char *s1);
//char				*ft_strsub(char const *s, unsigned int start, size_t len);
//size_t				ft_strlen(const char *s);
//t_list				*ft_lstnew(void const *content, size_t content_size);
//void				ft_lst_delone(t_list **f, t_list *one,
//                                  void (*del)(t_list *));
//void				ft_list_clear(t_list *node);
//void				ft_list_add(t_list **first_node, t_list *new_node);
//int					ft_str_contains(char *source, char *target);
//char				**ft_splinter(char const *s, char *c);
//void				ft_memdel(void **ap);
//int					ft_atoi(const char *str);
//char				*ft_strjoin(char const *s1, char const *s2);
//int					ft_strequ(char const *s1, char const *s2);

#define TO_FLOAT(x) (float)x * 1.0

typedef	struct		s_map_vertex
{
	// char					*neighbor;
	int						neighbor;
	int						x;
	int						y;

	struct	s_map_vertex 	*next;
}					t_map_vertex;

typedef	struct		s_map_sector
{
	t_map_vertex	*vertex;
	int				vertex_size;

	int				floor;
	int				ceil;

	char			*next_level;
	int				next_level_sector;

	struct	s_map_sector 	*next;
}					t_map_sector;


typedef	struct		s_map
{
	t_map_sector	*sector;
	int				sector_size;

    char 			*floortexture;
    char 			*ceiltexture;
    char 			*uppertextures;
    char 			*lowertextures;
    int          	texture_size;
    
}					t_map;

t_map_vertex		*map_new_vertex();
void				map_add_vertex(t_map_vertex **first, t_map_vertex *new);
void				map_del_vertex(t_map_vertex **node);

t_map_sector		*map_new_sector();
void				map_add_sector(t_map_sector **first, t_map_sector *new);
void				map_del_sector(t_map_sector **node);

char				*str_cut(char *line, int start, int end);
char				*cut_str_value(char *line, char *start, char *end);
void  				loop_str_to_value(char **line, char *value, int condition);
int					char_isdigit(int c);
int					str_isdigit(char *s);

void 				free_splinter(char **splt, int size);
int 				parse_atoi(char *str);
int 				parse_singe_value(char **line, char *flag, char *separ);
int    				iterate(int max);
int 				catch_exception(int status);

void				parse_vertex_switch(t_map_vertex *vertex, char * str, int condition);
void 				parse_vertex(char **vertex, t_map_vertex **fvertex, int *count, int *size);
t_map_vertex 		*parse_sector(char **line, int *count);

char 				*parse_level(char **line, int *nxt_sector);
void 				parse_level_info(char **lvl_info, int *it, char **nxt_lvl, int *nxt_sctr);

void 				parse_line(char **line, t_map_sector **map_sector );
t_map   			*parser(char *line, int status);

sectors *connect_sectors(t_map *map);
texture_set_s   connect_textures(t_map *map);
level_s connect_level(t_map *map);
t_map *get_map(char *file_name);
//typedef struct level_s
//{
//    sectors 		*sector;
//    texture_set_s  	textures;
//    int 			sectors_size;
//    int start[3];
//    int end[3];
//    int next_level[3];
//}           level_s;




#endif
