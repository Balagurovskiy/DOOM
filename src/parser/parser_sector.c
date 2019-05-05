
#include "parser.h"
#include "libft.h"

void parse_vertex_switch(t_map_vertex *vertex, char * str, int condition)
{
	if (condition == 0)
		vertex->x = parse_atoi(str);
	if (condition == 1)
		vertex->y = parse_atoi(str);
	if (condition == 2)
		vertex->neighbor = parse_atoi(str);
}

void parse_vertex(char **vertex, t_map_vertex **fvertex, int *count, int *size)
{	
	int 			it;
	t_map_vertex 	*v_next;

	it = 0;
	v_next = NULL;
	while (vertex && vertex[(*size)])
	{
		if (it == 0){
			(*count)++;
			v_next = map_new_vertex();
		}
		parse_vertex_switch(v_next, vertex[(*size)], it);
		if (it == 2){
			map_add_vertex(fvertex, v_next);
		}
		it = iterate(3);
		(*size)++;
	}
	if (it != 0)
	{
		ft_putstr("EXCEPTION > parser > invalid sector data size\n");
		catch_exception(1);
	}
}

t_map_vertex 	*parse_sector(char **line, int *count)
{
	t_map_vertex 	*fvertex;
	char 			*sectors;
	char 			**vertex;
	int 			size;
	
	size = 0;
	(*count) = 0;
	fvertex = NULL;
	sectors = cut_str_value(*line, "sector:\0", ";\0");
    vertex = ft_splinter(sectors, ",{}");
    if (!sectors || !vertex)
    {
        ft_putstr("EXCEPTION > parser > invalid sector data format\n");
        catch_exception(1);
    }
    else
        parse_vertex(vertex, &fvertex, count, &size);
    free_splinter(vertex, size);
    loop_str_to_value(line, ";\0", sectors != NULL);
    ft_memdel((void **)&sectors);
	return (fvertex);
}