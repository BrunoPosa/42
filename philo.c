/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/07/23 19:58:28 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*routine(t_data *d)
{
	if (prep(d) == ERROR)
		return (cleanerr(d, ERROR, d->n_philos));
	printf("\nroutine\n");
	return (SUCCESS);
}

// int	conductor(t_data *d)
// {

// }

/*
	TODO:
	-fix validator() to work using macros
	-reorganize initialization
	-have a conductor()/monitor function to run the simulation
*/
int main(int argc, char **argv)
{
	t_data	*d;

	if (validator(argc, argv) == ERROR)
		return (ermsg(EVAL));
	d = malloc(sizeof(t_data));
	if (!d)
		return (ermsg(EMALLOC));
	memset(d, 0, sizeof(t_data));
	if (initor(argv, d) == ERROR)
		return (ermsg(EINIT));

	// if (conductor(d) == ERROR)
	// 	return (cleanerr(d, ERROR, d->n_philos));

	cleanerr(d, SUCCESS, d->n_philos);
	return (SUCCESS);
}
