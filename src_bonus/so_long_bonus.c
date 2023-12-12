/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:04:59 by akanbari          #+#    #+#             */
/*   Updated: 2023/11/23 17:27:54 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static	void	key_hooks_helper(t_mygame *game)
{
	draw_map(game);
	game->steps++;
	printf("STEPS =  '%d'\n", game->steps);
}

int	key_hooks(int keycode, t_mygame *game)
{
	if (keycode == ESC)
		finish_game(game);
	if (keycode == W || keycode == UP)
	{
		move_up(game);
		game->movement_flag = 0;
	}
	if (keycode == S || keycode == DOWN)
	{
		move_down(game);
		game->movement_flag = 1;
	}
	if (keycode == A || keycode == LEFT)
	{
		move_left(game);
		game->movement_flag = 2;
	}
	if (keycode == D || keycode == RIGHT)
	{
		move_right(game);
		game->movement_flag = 3;
	}
	if (keycode == D || keycode == A || keycode == W || keycode == S || \
	keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		key_hooks_helper(game);
	return (0);
}

static void	general_initializer(t_mygame *game)
{
	check_ber(game);
	ft_savemap(game);
	game->vars.size_x = ft_strlen(game->map[0]) - 1;
	isrectangle(game);
	ft_check_surr_walls(game);
	initialize_game(game);
	checking_map(game);
	set_variables(game);
	game->vars.mlx = mlx_init();
	load_objects_tomlx(game);
	game->map_size.h = game->vars.size_y * SIZE_PXL;
	game->map_size.w = game->vars.size_x * SIZE_PXL;
	check_paths(game);
	game->vars.window = mlx_new_window(game->vars.mlx, game->map_size.w, \
			game->map_size.h, GAME_NAME);
}

int	main(int ac, char **av)
{
	t_mygame	game;

	if (ac != 2)
		return (ft_printf("Only 2 argumenst are allowed"), \
		exit(1), 0);
	game.maplink = av[1];
	general_initializer(&game);
	draw_map(&game);
	mlx_key_hook(game.vars.window, key_hooks, &game);
	mlx_hook(game.vars.window, 17, 0, finish_game_won, &game);
	mlx_hook(game.vars.window, 17, 0, finish_game_lost, &game);
	mlx_loop_hook(game.vars.mlx, update_window, &game);
	mlx_loop(game.vars.mlx);
}
