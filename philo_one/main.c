/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 12:07:04 by henri             #+#    #+#             */
/*   Updated: 2020/03/29 00:51:41 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			clear(void)
{
	int 			i;

	i = -1;
	if (context.mutexforks)
		while (++i < context.philosophers)
			pthread_mutex_destroy(&context.mutexforks[i]);
	free(context.mutexforks);
	i = -1;
	if (context.philos)
		while (++i < context.philosophers)
			pthread_mutex_destroy(&context.philos[i].philomutex);
	free(context.philos);
	pthread_mutex_destroy(&context.mutexdeath);
	pthread_mutex_destroy(&context.mutexwrite);
	return (1);
}

/*
** La fonction watching() surveille qu'aucun philosophe ne meure
** Un philosophe meurt s'il n'est pas entrain de manger et que son temps de
** survie depuis le dernier est depassé
** Si c'est le cas, on unlock mutexdeath qui fait que le main se termine
** On usleep() pour pas toujours avoir le philo->philomutex de locké,
** car autrement, ca ralentirai largement les actions
*/

static void			*watching(void *philo_uncasted)
{
	t_philo 		*philo;

	philo = (t_philo*)philo_uncasted;
	while (42)
	{
		pthread_mutex_lock(&philo->philomutex);
		if (philo->is_eating == 0 && philo->remainingtime < chrono())
		{
			printstatus(philo, "died");
			pthread_mutex_unlock(&philo->philomutex);
			pthread_mutex_unlock(&context.mutexdeath);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->philomutex);
		usleep(1000);
	}

}

/*
** no_eat_limit() intervient quand il n'y a pas de limite de repas
** philo->last_meal = chrono();
** Cette ligne sert juste d'initialisation avant le premier repas d'un philo
** On crée un thread  moniteur (detaché) du thread appartenant au philo X
** On essaie dans le while (1) de prendre les 2 fourchettes voisines
** 	- Si oui le philo mange, libère les 2 fourchettes, dors puis pense
*/

static void			*noeatlimit(void *philo_uncasted)
{
	t_philo 	*philo;
	pthread_t	subthread;

	philo = (t_philo*)philo_uncasted;
	philo->last_meal = chrono();
	philo->remainingtime = philo->last_meal + context.time_to_die;
	if (pthread_create(&subthread, NULL, &watching, philo))
		return ((void*)1);
	pthread_detach(subthread);
	while (42)
	{
		lock2forks(philo);
		eat(philo);
		sleep_unlock2forks(philo);
		printstatus(philo, "is thinking");
 	}
	return ((void*)0);
}

/*
** On crée un thread détaché pour chaque philosophe
** On usleep(100) pour éviter qu'au début ils prennent tous leurs baguettes
** en même temps et génèrent un deadlock
*/

static int		start(void)
{
	int			i;
	void		*philo;
	pthread_t	thread;

	i = -1;
	context.timer = chrono();
	while (++i < context.philosophers)
	{
		philo = (void*)(&context.philos[i]);
		if (pthread_create(&thread, NULL, &noeatlimit, philo))
			return (1);
		pthread_detach(thread);
		usleep(100);
	}
	return (0);
}

/*
** On attend à pthread_mutex_lock(&context.mutexdeath) jusqu'à ce qu'un
** philosophe meurt
** On va wait la ligne pthread_mutex_lock(&context.mutexdeath);
** jusqu'à ce qu'un philosophe meurt car on a lock le mutex dans initmutex()
** auparavant
** Pour rappel, un "lock sur mutex déjà lock" = "wait jusqu'à unlock du mutex"
*/

int		main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		putstrfd("Errror: wrong number of arguments\n", 2);
		return (1);
	}
	if (initcontext(ac, av))
	{
		clear();
		putstrfd("Error: initialization\n", 2);
		return (1);
	}
	if (start())
	{
		clear();
		putstrfd("Error: core function\n", 2);
		return (1);
	}
	pthread_mutex_lock(&context.mutexdeath);
	pthread_mutex_unlock(&context.mutexdeath);
	clear();
	return (0);
}
