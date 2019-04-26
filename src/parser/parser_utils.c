
#include "parser.h"
# include "libft.h"

int 	catch_exception(int status)
{
	static int entry = 0;

	if(status)
		entry++;
	return (entry);
}

int    iterate(int max)
{
	static int i = 0;
	
	i++;
	if (i == max)
		i = 0;
	return (i);
}

int parse_singe_value(char **line, char *flag, char *separ)
{
	int 	value;
	char 	*segment;

	segment = cut_str_value(*line, flag, separ);
	value = parse_atoi(segment);
	loop_str_to_value(line, separ, (segment != NULL));
	ft_memdel((void **)&segment);
	return (value);
}

int parse_atoi(char *str)
{
	int value;

	if (str && str_isdigit(str))
	{
		value = ft_atoi((const char *)str);
	}
	else
	{
		ft_putstr("EXCEPTION > parser > not a digit input\n");
		value = -666;
		catch_exception(1);
	}
	return (value);
}

void free_splinter(char **splt, int size)
{
	int j;

	j = -1;
	if (!splt)
		return ;
	while (++j < size)
		ft_memdel((void **)&(splt[j]));
	ft_memdel((void **)&(splt));
}