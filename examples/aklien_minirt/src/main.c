/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:38 by jtu               #+#    #+#             */
/*   Updated: 2024/09/22 14:27:30 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	render(void)
{
	render_scene();
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error(E_PARSER, "Wrong argument number!");
	ft_bzero(rtx(), sizeof(t_rtx));
	parse_input(argv);
	clear_lal();
	init_rtx();
	setup_scene();
	render();
	mlx_key_hook(rtx()->mlx, key_hook, rtx());
	mlx_loop_hook(rtx()->mlx, loop_hook, rtx());
	mlx_resize_hook(rtx()->mlx, resize_hook, rtx());
	mlx_loop(rtx()->mlx);
	error(E_NOPE, NULL);
	return (0);
}