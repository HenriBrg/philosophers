/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 15:38:15 by henri             #+#    #+#             */
/*   Updated: 2020/05/14 22:54:52 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				printstatus(t_philo *philo, char *str)
{
	static int	x;

	if (sem_wait(g_context.semawrite))
		return (1);
	if (x == 0)
	{
		putuint64_t(1, chrono() - g_context.timer);
		write(1, "\t", 1);
		if (strcompare(str, "maximum meal reached") == 0)
		{
			putstrfd("max eat reached\n", 1);
			x = 1;
			return (sem_post(g_context.semawrite) == 0 ? 0 : 1);
		}
		putuint64_t(1, ((uint64_t)philo->pos + 1));
		write(1, " ", 1);
		putstrfd(str, 1);
		write(1, "\n", 1);
		if (strcompare(str, "died") == 0)
			x = 1;
	}
	if (sem_post(g_context.semawrite))
		return (1);
	return (x == 1 ? 1 : 0);
}

/*
** On lock 2 fourchettes pour pouvoir manger, si indisponible on attend
** Sachant que les fourchettes sont au centre et non entre chaque philosophe
*/

int				lock2forks(t_philo *philo)
{
	if (sem_wait(g_context.semaforks))
		return (1);
	if (printstatus(philo, "has taken a fork"))
		return (1);
	if (sem_wait(g_context.semaforks))
		return (1);
	if (printstatus(philo, "has taken a fork"))
		return (1);
	return (0);
}

int				sleep_unlock2forks(t_philo *philo)
{
	if (printstatus(philo, "is sleeping"))
		return (1);
	if (sem_post(g_context.semaforks))
		return (1);
	if (sem_post(g_context.semaforks))
		return (1);
	usleep(g_context.time_to_sleep * 1000);
	return (0);
}

/*
** On lock le mutex appartenant au philosophe concerné
** usleep * 1000 pour les milisecondes
*/

int				eat(t_philo *philo)
{
	if (sem_wait(philo->philosema))
		return (1);
	philo->last_meal = chrono();
	philo->remainingtime = philo->last_meal + g_context.time_to_die;
	if (printstatus(philo, "is eating"))
		return (1);
	philo->meal_count += 1;
	usleep(g_context.time_to_eat * 1000);
	if (sem_post(philo->philosema))
		return (1);
	if (sem_post(philo->philosemaeatcount))
		return (1);
	return (0);
}
