/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 16:43:10 by henri             #+#    #+#             */
/*   Updated: 2020/03/27 16:43:51 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		initphilos(int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		context.philos[i].pos = i;
		context.philos[i].is_eating = 0;
		context.philos[i].last_meal = 0;
		context.philos[i].meal_count = 0;
		context.philos[i].lfork = i;
		context.philos[i].rfork = (i + 1 != number) ? i + 1 : 0;
		i++;
	}
}

static int		initmutex(int number)
{
	int	i;

	context.mutexforks = NULL;
	if ((context.mutexforks = malloc(sizeof(pthread_mutex_t) * number)) == 0)
		return (1);
	i = -1;
	while (++i < number)
		pthread_mutex_init(&(context.mutexforks[i]), NULL);
	pthread_mutex_init(&(context.mutexdeath), NULL);
	pthread_mutex_init(&(context.mutexwrite), NULL);
	// Lock death ?
	return (0);
}

int				initcontext(int ac, char **av)
{
	context.philosophers = ft_atoi(av[1]);
	context.time_to_die = ft_atoi(av[2]);
	context.time_to_eat = ft_atoi(av[3]);
	context.time_to_sleep = ft_atoi(av[4]);
	context.number_of_meal = (ac == 6) ? ft_atoi(av[5]) : 0;
	if (context.philosophers < 2 || context.philosophers > 100 ||
		context.time_to_die < 100 || context.time_to_eat < 100 ||
		context.time_to_sleep < 100 || context.number_of_meal < 0)
		return (1);
	context.philos = NULL;
	if ((context.philos = malloc(sizeof(t_philo) * context.philosophers)) == 0)
		return (1);
	initphilos(context.philosophers);
	return (initmutex(context.philosophers));

}
