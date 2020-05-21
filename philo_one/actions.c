/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 15:38:15 by henri             #+#    #+#             */
/*   Updated: 2020/05/21 19:40:52 by henri            ###   ########.fr       */
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
		if (strcompare(str, "maximum meal reached") == 0)
		{
			putstrfd("max eat reached\n", 1);
			x = 1;
			pthread_mutex_unlock(&g_context.mutexwrite);
			return ;
		}
		putuint64_t(1, ((uint64_t)philo->pos + 1));
		write(1, " ", 1);
		putstrfd(str, 1);
		write(1, "\n", 1);
		if (strcompare(str, "died") == 0)
			x = 1;
	}
	pthread_mutex_unlock(&g_context.mutexwrite);
}

/*
** On lock 2 fourchettes pour pouvoir manger, si indisponible on attend
** Sachant que les fourchettes sont au centre et non entre chaque philosophe
**
** usleep(500) sur conseil, idk why
*/

void			lock2forks(t_philo *philo)
{
	pthread_mutex_lock(&g_context.mutexforks[philo->lfork]);
	printstatus(philo, "has taken a fork");
	usleep(50);
	pthread_mutex_lock(&g_context.mutexforks[philo->rfork]);
	printstatus(philo, "has taken a fork");
}

void			sleep_unlock2forks(t_philo *philo)
{
	printstatus(philo, "is sleeping");
	pthread_mutex_unlock(&g_context.mutexforks[philo->lfork]);
	pthread_mutex_unlock(&g_context.mutexforks[philo->rfork]);
	usleep(g_context.time_to_sleep * 1000);
	usleep(500);
}

/*
** On lock le mutex appartenant au philosophe concerné
** usleep * 1000 pour les milisecondes
*/

void			eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philomutex);
	philo->last_meal = chrono();
	philo->remainingtime = philo->last_meal + g_context.time_to_die;
	printstatus(philo, "is eating");
	philo->meal_count += 1;
	usleep(g_context.time_to_eat * 1000);
	pthread_mutex_unlock(&philo->philomutex);
	pthread_mutex_unlock(&philo->philomutexeatcount);
}
