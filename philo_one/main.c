/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 12:07:04 by henri             #+#    #+#             */
/*   Updated: 2020/03/28 00:03:56 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**  Avec #include <inttypes.h>
** 	printf("Timer : %" PRIu64 "\n", chrono());
*/


void	*schedule(void *philo)
{
	t_philo *philo;

	philo = (t_philo*)philo;


}

void	*handlethread(void *philo)
{
	t_philo 	*philo;
	pthread_t	subthread;

	philo = (t_philo*)philo;
	philo->last_meal = chrono();
	philo->remainingtime = philo->last_meal + context.time_to_die;
	if (pthread_create(&subthread, NULL, schedule, philo))
		return ((void*)1);
	pthread_detatch(&subthread);
	while (1)
	{
		lockfork();
		eat();

	}
}

int		start(void)
{
	int			i;
	void		*philo;
	pthread_t	thread;

	i = -1;
	context.timer = chrono();
	while (++i < context.philosophers)
	{
		philo = (void*)(&context.philos[i]);
		if (pthread_create(&thread, NULL, handlethread, philo))
			return (1);
		pthread_detatch(thread);
		// Trouver pourquoi on sleep ici
		usleep(100);
	}
	return (0);
}

int		main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		putstrfd("Errror: wrong number of arguments\n", 2);
		return (1);
	}
	if (initcontext(ac, av))
	{
		// Free context.philos + context
		putstrfd("Error: initialization\n", 2);
		return (1);
	}
	return (0);
}
