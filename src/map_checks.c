/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:49:41 by hrisse            #+#    #+#             */
/*   Updated: 2025/05/28 15:49:50 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/ft_printf.h"
#include "../includes/map_path.h"

static int	check_map_counts(t_map *map)
{
	if (map->player != 1)
	{
		ft_printf("Error\nMap must have exactly one player position\n");
		return (0);
	}
	if (map->exit != 1)
	{
		ft_printf("Error\nMap must have exactly one exit\n");
		return (0);
	}
	if (map->collectibles == 0)
	{
		ft_printf("Error\nMap must have at least one collectible\n");
		return (0);
	}
	return (1);
}

static int	process_map_char(t_map *map, int x, int y)
{
	char	c;

	c = map->grid[y][x];
	if (c == 'P')
		map->player++;
	else if (c == 'E')
	{
		map->exit++;
		map->exit_x = x;
		map->exit_y = y;
	}
	else if (c == 'C')
		map->collectibles++;
	else if (c != '0' && c != '1')
	{
		ft_printf("Error\nInvalid character '%c' at position (%d,%d)\n",
			c, y, x);
		return (0);
	}
	return (1);
}

static int	validate_map_chars(t_map *map)
{
	int	x;
	int	y;

	map->player = 0;
	map->exit = 0;
	map->collectibles = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!process_map_char(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_requirements(t_map *map)
{
	char	**visited;
	int		status;

	if (!validate_map_chars(map) || !check_map_counts(map))
		return (0);
	visited = create_visited_map(map);
	if (!visited)
	{
		ft_printf("Error\nMemory allocation failed\n");
		return (0);
	}
	status = check_reachable_items(map, visited);
	if (status)
		free_visited(visited, map->height);
	return (status);
}
