/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:28:06 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/23 18:29:56 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"
#include <math.h>

char	*skip_space(char *s)
{
	if (!s)
		return (NULL);
	while (*s && *s == ' ')
		s++;
	return (s);
}

int	does_file_end_with_rt(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 3)
		return (0);
	if (ft_strncmp(&filename[len - 3], ".rt", 3))
		return (0);
	return (1);
}

void	esc_keyhook(mlx_key_data_t keydata, void *param)
{
	t_rt	*data;

	data = param;
	if (!param || !data->mlx)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

float	calculate_focal_len(unsigned int fov)
{
	float	fov_radians;
	float	focal_len;

	fov_radians = (fov * M_PI) / 180.0;
	focal_len = 1 / tan(fov_radians / 2.0);
	return (focal_len);
}

uint32_t	to_uint32(t_colour colour)
{
	uint32_t	c;

	c = 255 << 24
		| (uint32_t)(clamp(colour.b)) << 16
		| (uint32_t)(clamp(colour.g)) << 8
		| (uint32_t)(clamp(colour.r));
	return (c);
}
