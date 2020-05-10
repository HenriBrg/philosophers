/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 16:43:10 by henri             #+#    #+#             */
/*   Updated: 2020/05/10 17:31:33 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void 			clear(void)
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
		{
			pthread_mutex_destroy(&context.philos[i].philomutex);
			pthread_mutex_destroy(&context.philos[i].philomutexeatcount);
		}
	free(context.philos);
	pthread_mutex_destroy(&context.mutexdeath);
	pthread_mutex_destroy(&context.mutexwrite);
}

/*
** Le table est circulaire donc le dernier philosophe est voisin du premier
** D'où le ternaire (i + 1 != number) ? i + 1 : 0
*/

static void		initphilos(int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		context.philos[i].pos = i;
		context.philos[i].last_meal = 0;
		context.philos[i].meal_count = 0;
		context.philos[i].lfork = i;
		context.philos[i].rfork = (i + 1 != number) ? i + 1 : 0;
		pthread_mutex_init(&context.philos[i].philomutex, NULL);
		pthread_mutex_init(&context.philos[i].philomutexeatcount, NULL);
		pthread_mutex_lock(&context.philos[i].philomutexeatcount);
		i++;
	}
}

/*
** On lock mutexdeath car c'est la condition de sortie du main
** Le pthread_mutex_lock(mutexdeath) ici permet de wait jusqu'à une mort
** dans le 2nd call de pthread_mutex_lock(mutexdeath) du main
*/

static int		initmutex(int number)
{
	int	i;

	context.mutexforks = NULL;
	if ((context.mutexforks = malloc(sizeof(pthread_mutex_t) * number)) == 0)
		return (1);
	i = -1;
	while (++i < number)
		pthread_mutex_init(&context.mutexforks[i], NULL);
	pthread_mutex_init(&context.mutexdeath, NULL);
	pthread_mutex_lock(&context.mutexdeath);
	pthread_mutex_init(&context.mutexwrite, NULL);
	return (0);
}

int				initcontext(int ac, char **av)
{
	context.philosophers = ft_atoi(av[1]);
	context.time_to_die = ft_atoi(av[2]);
	context.time_to_eat = ft_atoi(av[3]);
	context.time_to_sleep = ft_atoi(av[4]);
	context.maxeat = (ac == 6) ? ft_atoi(av[5]) : 0;
	if (context.philosophers < 2 || context.philosophers > 200 ||
		context.time_to_die < 50 || context.time_to_eat < 50 ||
		context.time_to_sleep < 50 || context.maxeat < 0)
		return (1);
	context.philos = NULL;
	if ((context.philos = malloc(sizeof(t_philo) * context.philosophers)) == 0)
		return (1);
	initphilos(context.philosophers);
	return (initmutex(context.philosophers));
}
