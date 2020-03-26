/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 12:07:04 by henri             #+#    #+#             */
/*   Updated: 2020/03/27 00:26:45 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initmutex(int number)
{
	int	i;

	if ((context.mutexforks = malloc(sizeof(pthread_mutex_t) * number)) == 0)
		putexit(1, "Error: malloc context.mutexforks\n");
	i = -1;
	while (++i < number)
		pthread_mutex_init()

}

void	initphilos(int number)
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

void	initcontext(int ac, char **av)
{
	context.philosophers = ft_atoi(av[1]);
	context.time_to_die = ft_atoi(av[2]);
	context.time_to_eat = ft_atoi(av[3]);
	context.time_to_sleep = ft_atoi(av[4]);
	context.number_of_meal = (ac == 6) ? ft_atoi(av[5]) : 0;
	if (context.philosophers < 2 || context.philosophers > 100 ||
		context.time_to_die > 30 || context.time_to_eat > 30 ||
		context.time_to_sleep > 30 || context.number_of_meal < 0)
		putexit(1, "Error: invalid arguments\n");
	context.philos = NULL;
	if ((context.philos = malloc(sizeof(t_philo) * context.philosophers)) == 0)
		putexit(1, "Error: malloc context.philos\n");
	initphilos(context.philosophers);
	initmutex(context.philosophers);

}

int		main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		putexit(1, "Errror: wrong number of arguments\n");
	init(ac, av);
	return (0);
}
