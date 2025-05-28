/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:52:45 by hrisse            #+#    #+#             */
/*   Updated: 2025/05/28 15:52:50 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/ft_printf.h"

void	find_player_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

static int	handle_exit(t_game *game)
{
	if (game->map.collectibles == 0)
	{
		ft_printf("\nVictory! You collected all items and reached the exit!\n");
		close_game(game);
		return (0);
	}
	ft_printf("\nYou need to collect all items before you can exit! "
		"(%d remaining)\n", game->map.collectibles);
	return (1);
}

static void	update_player_pos(t_game *game, int x, int y)
{
	if ((game->map.exit_x == game->player_x)
		&& (game->map.exit_y == game->player_y))
		game->map.grid[game->player_y][game->player_x] = 'E';
	else
		game->map.grid[game->player_y][game->player_x] = '0';
	game->player_x = x;
	game->player_y = y;
	game->map.grid[y][x] = 'P';
}

static int	handle_collision(t_game *game, int x, int y)
{
	char	current;

	current = game->map.grid[y][x];
	if (current == 'C')
	{
		game->map.collectibles--;
		update_player_pos(game, x, y);
		return (1);
	}
	else if (current == 'E')
	{
		if (handle_exit(game))
		{
			update_player_pos(game, x, y);
			return (1);
		}
		return (0);
	}
	update_player_pos(game, x, y);
	return (1);
}

/*
** [18] Attempts to move player to new position
** Checks map boundaries and wall collisions
** Updates move counter and redraws map if successful
** Returns 1 if movement succeeded, 0 otherwise
*/
int	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x >= 0
		&& new_x < game->map.width
		&& new_y >= 0
		&& new_y < game->map.height
		&& game->map.grid[new_y][new_x] != '1')
	{
		if (handle_collision(game, new_x, new_y))
		{
			game->moves++;
			ft_printf("Moves: %d\n", game->moves);
			draw_map(game);
			return (1);
		}
	}
	return (0);
}
