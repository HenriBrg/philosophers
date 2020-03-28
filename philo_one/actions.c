/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 15:38:15 by henri             #+#    #+#             */
/*   Updated: 2020/03/28 22:28:12 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Left / Right forks problem

void		printstatus(t_philo *philo, char *status)
{
	static int dead;

	pthread_mutex_lock(&context.mutexwrite);
	if (dead == 0)
	{
		putuint64_t(1, chrono() - context.timer);
		write(1, "\t", 1);
		write(1, "philo ", 6);
		putuint64_t(1, ((uint64_t)philo->pos + 1));
		write(1, " ", 1);
		if (strcompare(status, "has taken a fork (left)") == 0)
		{
			putstrfd("has taken the fork (at his left)  n°", 1);
			putuint64_t(1, ((uint64_t)philo->pos + 1));
		}
		else if (strcompare(status, "has taken a fork (right)") == 0)
		{
			putstrfd("has taken the fork (at his right) n°", 1);
			putuint64_t(1, (context.philosophers - (uint64_t)philo->pos));
		}
		else
			putstrfd(status, 1);
		write(1, "\n", 1);
		if (strcompare(status, "died") == 0)
			dead = 1;
	}
	pthread_mutex_unlock(&context.mutexwrite);
}

void		lock2forks(t_philo *philo)
{
	pthread_mutex_lock(&context.mutexforks[philo->lfork]);
	printstatus(philo, "has taken a fork (left)");
	pthread_mutex_lock(&context.mutexforks[philo->rfork]);
	printstatus(philo, "has taken a fork (right)");
}

 */

void			printstatus(t_philo *philo, char *status)
{
	static int	dead;

	pthread_mutex_lock(&context.mutexwrite);
	if (dead == 0)
	{
		putuint64_t(1, chrono() - context.timer);
		write(1, "\t", 1);
		putuint64_t(1, ((uint64_t)philo->pos + 1));
		write(1, " ", 1);
		putstrfd(status, 1);
		write(1, "\n", 1);
		if (strcompare(status, "died") == 0)
			dead = 1;
	}
	pthread_mutex_unlock(&context.mutexwrite);
}

/*
** On lock 2 fourchettes pour pouvoir manger, si indisponible on attend
** Sachant que les fourchettes sont au centre et non entre chaque philosophe
*/

void			lock2forks(t_philo *philo)
{
	pthread_mutex_lock(&context.mutexforks[philo->lfork]);
	printstatus(philo, "has taken a fork");
	pthread_mutex_lock(&context.mutexforks[philo->rfork]);
	printstatus(philo, "has taken a fork");
}

void			sleep_unlock2forks(t_philo *philo)
{
	printstatus(philo, "is sleeping");
	pthread_mutex_unlock(&context.mutexforks[philo->rfork]);
	pthread_mutex_unlock(&context.mutexforks[philo->rfork]);
	usleep(context.time_to_sleep * 1000);
}

void			eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_philo_boolean);
	philo->is_eating = 1;
	philo->last_meal = chrono();
	philo->remainingtime = philo->last_meal + context.time_to_die;
	printstatus(philo, "is eating");
	usleep(context.time_to_eat * 1000);
	philo->meal_count += 1;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex_philo_boolean);
	pthread_mutex_unlock(&philo->mutex_eat_boolean);
}
