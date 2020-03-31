/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 16:43:10 by henri             #+#    #+#             */
/*   Updated: 2020/03/31 19:07:48 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Retourne un string équivalent à name+id pour différencier
** les N sémaphores
*/

char			*semanames(char *name, int id, int eat)
{
	int i;
	const char basename1[6] = "philo-";
	const char basename2[10] = "philo-eat-";

	i = -1;
	if (eat)
		while (++i < 10)
			name[i] = basename2[i];
	else
		while (++i < 6)
			name[i] = basename1[i];
	while (id)
	{
		name[i++] = (id % 10) + '0';
		id /= 10;
	}
	name[i] = '\0';
	return (name);
}

void 			clear(void)
{
	int 			i;
	char			name[50];

	i = -1;
	sem_unlink(SEMAFORKS);
	sem_unlink(SEMAWRITE);
	sem_unlink(SEMADEATH);
	if (context.philos)
		while (++i < context.philosophers)
		{
			semanames(name, i + 1, PHI_INIT);
			sem_unlink(name);
			semanames(name, i + 1, EAT_INIT);
			sem_unlink(name);
		}
	free(context.philos);
}

/*
** Le table est circulaire donc le dernier philosophe est voisin du premier
** D'où le ternaire (i + 1 != number) ? i + 1 : 0
*/

static int		initphilos(void)
{
	int	i;
	char			name[50];

	i = 0;
	while (i < context.philosophers)
	{
		context.philos[i].pos = i;
		context.philos[i].last_meal = 0;
		context.philos[i].meal_count = 0;
		semanames(name, i + 1, PHI_INIT);
		sem_unlink(name);
		if ((context.philos[i].philosema =
			sem_open(name, O_CREAT | O_EXCL, 0644, i + 1)) == SEM_FAILED)
			return (1);
		semanames(name, i + 1, EAT_INIT);
		sem_unlink(name);
		if ((context.philos[i].philosemaeatcount =
			sem_open(name, O_CREAT | O_EXCL, 0644, i + 1)) == SEM_FAILED)
			return (1);
		i++;
	}
}

static int		initsemas(void)
{
	sem_unlink(SEMAFORKS);
	sem_unlink(SEMAWRITE);
	sem_unlink(SEMADEAD);
	if ((context.semaforks = sem_open(SEMAFORKS, O_CREAT | O_EXCL, 0644, context.philosophers)) == SEM_FAILED)
		return (1);
	if ((context.semawrite = sem_open(SEMAWRITE, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (1);
	if ((context.semadeath = sem_open(SEMADEATH, O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED)
		return (1);
	return (0);
}

int				initcontext(int ac, char **av)
{
	context.philosophers = ft_atoi(av[1]);
	context.time_to_die = ft_atoi(av[2]);
	context.time_to_eat = ft_atoi(av[3]);
	context.time_to_sleep = ft_atoi(av[4]);
	context.maxeat = (ac == 6) ? ft_atoi(av[5]) : 0;
	if (context.philosophers < 2 || context.philosophers > 100 ||
		context.time_to_die < 50 || context.time_to_eat < 50 ||
		context.time_to_sleep < 50 || context.maxeat < 0)
		return (1);
	context.philos = NULL;
	context.currenteatcounter = NULL;
	if ((context.philos = malloc(sizeof(t_philo) * context.philosophers)) == 0)
		return (1);
	if (initphilos())
		return (1);
	if (initsemas())
		return (1);
	return ();
}
