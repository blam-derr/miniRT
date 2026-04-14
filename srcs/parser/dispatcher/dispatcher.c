#include "miniRT.h"
#include "scene.h"
#include "parser.h"
#include "utils.h"
#include "vec.h"
#include <stdint.h>

uint8_t	parse_ambient(char **values, t_scene *scene)
{
	t_vec	color;

	if (string_array_length(values) != 5)
		return (0);
	scene->ambient.intensity = ft_atof(values[1]);
	color.x = ft_atof(values[2]);
	color.y = ft_atof(values[3]);
	color.z = ft_atof(values[4]);
	scene->ambient.color = color;
	return (1);
}

t_dispatched_fn	dispatch(char **values, t_scene *scene)
{
	int							i;
	int							len;
	static t_dict_dispatcher	dict[] = {
	{"A", parse_ambient},
	{"C", parse_ambient},
	{"L", parse_ambient},
	{"sp", parse_ambient},
	{"pl", parse_ambient},
	{"cy", parse_ambient},
	};

	i = 0;
	(void)scene;
	if (!values || !values[0])
		return (NULL);
	len = sizeof(dict) / sizeof(t_dict_dispatcher);
	while (i < len)
	{
		if (ft_strcmp(values[0], dict[i].key) == 0)
			return (dict[i].function);
		i++;
	}
	return (NULL);
}
