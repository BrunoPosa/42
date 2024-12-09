/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwadding <jwadding@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:49:50 by jwadding          #+#    #+#             */
/*   Updated: 2024/12/09 23:50:24 by jwadding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/file_to_list.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->diffuse_color)
		free(data->diffuse_color);
	if (data->shade_color)
		free(data->shade_color);
	data->shape = NULL;
	data->diffuse_color = NULL;
	data->shade_color = NULL;
	free(data);
	data = NULL;
}

// if we keep the list as one list, we can free like that?

// or we coudl section the list into different bits?

// free_list(t_scene *rt)
// {
// if there is a next, go there
// free that, go back?
// recursive?
// }
//
//
/// free all the memory allocated for the rt struct
// void free_rt(t_scene *rt)
// {
// 	free(rt->mlx);
// 	free(rt->img);
// 	free(rt->light);
// 	free(rt->camera);
// 	free(((void*)rt->ambiant));
// 	free_list(rt->cylinder);
// 	free_list(rt->plane);
// 	free_list(rt->sphere);
// 	(rt);
// }