/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 15:38:15 by henri             #+#    #+#             */
/*   Updated: 2020/05/27 22:24:53 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			printstatus(t_philo *philo, char *str)
{
	static int	x;

	pthread_mutex_lock(&g_context.mutexwrite);
	if (x == 0)
	{
		putuint64_t(1, chrono() - g_context.timer);
		write(1, "\t", 1);
		if (str[0] == 'm')
		{
			write(1, "max eat reached\n", 16);
			x = 1;
			pthread_mutex_unlock(&g_context.mutexwrite);
			return ;
		}
		putuint64_t(1, ((uint64_t)philo->pos + 1));
		write(1, " ", 1);
		putstrfd(str, 1);
		write(1, "\n", 1);
		if (str[0] == 'd')
			x = 1;
	}
	pthread_mutex_unlock(&g_context.mutexwrite);
}

/*
** On lock 2 fourchettes pour pouvoir manger, si indisponible on attend
** Sachant que les fourchettes sont au centre et non entre chaque philosophe
** struct timespec ts;
** ts.tv_sec = 0;
** ts.tv_nsec = g_context.time_to_sleep * 1000000;
** nanosleep(&ts, NULL);
*/

void			lock2forks(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(&g_context.mutexforks[philo->rfork]);
		printstatus(philo, "has taken a fork");
		pthread_mutex_lock(&g_context.mutexforks[philo->lfork]);
		printstatus(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&g_context.mutexforks[philo->lfork]);
		printstatus(philo, "has taken a fork");
		pthread_mutex_lock(&g_context.mutexforks[philo->rfork]);
		printstatus(philo, "has taken a fork");
	}
}

/*
** On lock le mutex appartenant au philosophe concerné
** usleep * 1000 pour les milisecondes
*/

void			eat(t_philo *philo)
{
	lock2forks(philo);
	pthread_mutex_lock(&philo->philomutex);
	philo->last_meal = chrono();
	philo->remainingtime = philo->last_meal + g_context.time_to_die;
	printstatus(philo, "is eating");
	philo->meal_count += 1;
	usleep(g_context.time_to_eat * 1000);
	pthread_mutex_unlock(&philo->philomutex);
	pthread_mutex_unlock(&philo->philomutexeatcount);
	printstatus(philo, "is sleeping");
	pthread_mutex_unlock(&g_context.mutexforks[philo->lfork]);
	pthread_mutex_unlock(&g_context.mutexforks[philo->rfork]);
	usleep(g_context.time_to_sleep * 1000);
	printstatus(philo, "is thinking");
}
