#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <pthread.h>
#include <semaphore.h>

// https://stackoverflow.com/questions/36755003/initialise-semaphores-using-sem-open


# define PHILOS 5
sem_t		*smph;

void			*monitor(void *arg)
{
	static int i;
	sem_wait(smph);
	printf("Hello %d\n", i);
	i++;
	sleep(1),
	sem_post(smph);
	return ((void*)0);
}

int				main(void)
{
	int 		i;
	pthread_t 	thread;

	if ((smph = sem_open("Sema", O_CREAT | O_EXCL, 0644, 1)) == 0)
		return (1);
	i = -1;
	while (++i < PHILOS)
	{
		pthread_create(&thread, NULL, &monitor, NULL);
		pthread_detach(thread);
	}
	sleep(15);
	printf("Unlink & Destroy\n");
	sem_unlink("Sema");
	if (sem_close(smph))
		return (1);
	return (0);
}
