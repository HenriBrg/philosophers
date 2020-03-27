#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

/*
** philosophers = nombre de philosophes et de fourchettes
** number_of_meal = nombre de fois qu'un philosophe doit manger (optionnel)
** lfork = fourchette gauche
*/

typedef struct		s_philo
{
	int				pos;
	int				is_eating;
	int				meal_count;
	int				lfork;
	int				rfork;
	uint64_t		last_meal;
	uint64_t		remainingtime;
}					t_philo;

typedef struct		s_context
{
	int				philosophers;
	int				number_of_meal;
	uint64_t		timer;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*mutexforks;
	pthread_mutex_t	mutexdeath;
	pthread_mutex_t	mutexwrite;
}					t_context;

t_context		context;

void			putstrfd(char *str, int fd);
int				ft_atoi(char *str);
int				initcontext(int ac, char **av);
void			putuint64_t(int fd, uint64_t timer);
uint64_t		chrono(void);

#endif
