/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 16:43:10 by henri             #+#    #+#             */
/*   Updated: 2020/05/14 22:54:23 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Retourne un string équivalent à name+id pour différencier
** les N sémaphores
** L'int eat vaut 0 si on doit retourner un name philo-id
** ou alors 1 si philo-eat-id
*/

void			semanames(char *name, int id, int eat)
{
	int			i;
	const char	basename1[6] = "philo-";
	const char	basename2[10] = "philo-eat-";

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
}

void			clear(void)
{
	int			i;
	char		name[50];

	i = -1;
	sem_unlink(SEMAFORKS);
	sem_unlink(SEMAWRITE);
	sem_unlink(SEMADEATH);
	if (g_context.philos)
	{
		while (++i < g_context.philosophers)
		{
			semanames(name, i + 1, PHI_INIT);
			sem_unlink(name);
			semanames(name, i + 1, EAT_INIT);
			sem_unlink(name);
		}
	}
	free(g_context.philos);
}

static int		initphilos(void)
{
	int			i;
	char		name[50];

	i = 0;
	while (i < g_context.philosophers)
	{
		g_context.philos[i].pos = i;
		g_context.philos[i].last_meal = 0;
		g_context.philos[i].meal_count = 0;
		semanames(name, i + 1, PHI_INIT);
		sem_unlink(name);
		if ((g_context.philos[i].philosema =
			sem_open(name, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
			return (1);
		semanames(name, i + 1, EAT_INIT);
		sem_unlink(name);
		if ((g_context.philos[i].philosemaeatcount =
			sem_open(name, O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED)
			return (1);
		i++;
	}
	return (0);
}

static int		initsemas(int philonum)
{
	sem_unlink(SEMAFORKS);
	sem_unlink(SEMAWRITE);
	sem_unlink(SEMADEATH);
	if ((g_context.semaforks =
		sem_open(SEMAFORKS, O_CREAT | O_EXCL, 0644, philonum)) == SEM_FAILED)
		return (1);
	if ((g_context.semawrite =
		sem_open(SEMAWRITE, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (1);
	if ((g_context.semadeath =
		sem_open(SEMADEATH, O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED)
		return (1);
	return (0);
}

/*
** Named semaphores content cannot be printed !
**
** To show context
** printf("NAME PHILO %d : %s\n", i, name);
** printf("NAME PHILO %d : %s\n", i, name);
** int i = 0;
** while (i < context.philosophers)
** {
** printf("philo %d pos : %d\n", i, context.philos[i].pos);
** printf("philo %d meal_count : %d\n", i, context.philos[i].meal_count);
** i++;
** }
*/

int				initcontext(int ac, char **av)
{
	g_context.philosophers = ft_atoi(av[1]);
	g_context.time_to_die = ft_atoi(av[2]);
	g_context.time_to_eat = ft_atoi(av[3]);
	g_context.time_to_sleep = ft_atoi(av[4]);
	g_context.maxeat = (ac == 6) ? ft_atoi(av[5]) : 0;
	if (g_context.philosophers < 2 || g_context.philosophers > 100 ||
		g_context.time_to_die < 50 || g_context.time_to_eat < 50 ||
		g_context.time_to_sleep < 50 || g_context.maxeat < 0)
		return (1);
	g_context.philos = NULL;
	g_context.globaleatcoutner = 0;
	if (!(g_context.philos = malloc(sizeof(t_philo) * g_context.philosophers)))
		return (1);
	if (initphilos())
		return (1);
	if (initsemas(g_context.philosophers))
		return (1);
	return (0);
}
