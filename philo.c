/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/08/08 13:15:01 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-Philo dies after some time with 200 130 60 60
	-it still sometimes prints "taken a fork" after death, e.g. with 200 130 60 60
	-try testing w/ fast debug optimization flag
	-./philo 200 599 200 200 should not die at 600 i think, but it often does. 
		AND rarely has some prints after death. 199 599 200 200 SHOUOLD die though.
	-Fix Helgrind
	-198 6 200 200 when giving small die_t, the printing continues a while after death
	-test 200 800 200 200 (none should die) Arthur fixed with every
		odd taking one fork first and even the other - BUT only on first run through. 
		Also waiting for sleep_t/2 to look for forks.
*/
void	routine(t_philo *p)
{
	setter(&p->ready, SUCCESS, &p->readylock);
	while (getter(&p->go, &p->golock) != GO)
		usleep(400);
	while (getter(&p->dead, &p->dlock) != DEATH)
	{
		printer(p->id, "is thinking", p);
		if (p->id % 2 == 0)
			wait_ms(5, p);
		pthread_mutex_lock(p->forkone);
		printer(p->id, "has taken a fork", p);
		if (p->last_meal_t == 0 && !p->forktwo && lastmealset(p))
		{
			pthread_mutex_unlock(p->forkone);
			break ;
		}
		pthread_mutex_lock(p->forktwo);
		printer(p->id, "has taken a fork", p);
		printer(p->id, "is eating", p);
		lastmealset(p);
		wait_ms(p->eat_t, p);
		pthread_mutex_unlock(p->forkone);
		pthread_mutex_unlock(p->forktwo);
		printer(p->id, "is sleeping", p);
		if (getter(&p->dead, &p->dlock) == DEATH || wait_ms(p->sleep_t, p))
			break ;
	}
}

void	butler(t_data *d)
{
	int	i;

	i = -1;
	while (checker(d, GO) != GO)
		usleep(400);
	d->starttime = get_time_ms();
	spread(d, GO);
	while (1)
	{
		i = -1;
		while (++i < d->n_philos)
		{
			if ((d->philo[i]->last_meal_t != 0 
				&& get_time_ms() - lastmealget(d->philo[i]) >= d->die_t)
				|| checker(d, MEAL) == SUCCESS)
			{
				spread(d, DEATH);
				break ;
			}
		}
		if (i != d->n_philos)
			break ;
	}
	if (checker(d, MEAL) != SUCCESS)
		printer(d->philo[i]->id, "died", d->philo[i]);
}

int	spread(t_data *d, int signal)
{
	int	i;

	i = -1;
	if (signal == DEATH)
	{
		while (++i < d->n_philos)
			setter(&d->philo[i]->dead, DEATH, &d->philo[i]->dlock);
		setter(&d->death, DEATH, &d->dielock);
	}
	else if (signal == GO)
	{
		while (++i < d->n_philos)
			setter(&d->philo[i]->go, GO, &d->philo[i]->golock);
	}
	return (SUCCESS);
}

void	printer(int arg, char *str, t_philo *p)
{
	if (getter(&p->dead, &p->dlock) == DEATH && my_strncmp(str, "died", 4) != SUCCESS)
		return ;
	pthread_mutex_lock(p->prlock);
	printf("%lld %d %s\n", get_time_ms() - *p->start_t, arg, str);
	if (my_strncmp(str, "died", 4) != SUCCESS)
		pthread_mutex_unlock(p->prlock);
	if (my_strncmp(str, "is eating", 9) == 0)
		p->meals_had++;
}

/*
	-Implement mutex lock/unlock protections..
	-fix validator() to work using macros/enums
	-reorganize initialization
	-Limit philos in validation to 2000
	-ensure when someone dies, NOTHING gets ever printed after that
*/
int main(int argc, char **argv)
{
	t_data	*d;

	if (validator(argc, argv) == ERROR)
		return (ermsg(EVAL));
	d = malloc(sizeof(t_data));
	if (!d)
		return (ermsg(EMALMUT));
	if (initor(argv, d) == ERROR)
		return (ermsg(EINIT));
	d->initdone = 1;
	while (getter(&d->death, &d->dielock) != DEATH)
		usleep(400);
	return (cleanerr(d, SUCCESS, d->n_philos));
}
