#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <pthread.h>
#include <semaphore.h>


// https://doc.riot-os.org/group__posix__semaphore.html

// https://stackoverflow.com/questions/36755003/initialise-semaphores-using-sem-open


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

# define PHILOS 5
sem_t		*smph;

void			*monitor(void *arg)
{
	if (sem_wait(smph))
	{
		fprintf(stdout, "FAIL\n");
		return ((void*)1);
	}
	// if (sem_wait(smph))
	// {
	// 	fprintf(stdout, "FAIL\n");
	// 	return ((void*)1);
	// }

	fprintf(stdout, "Hello\n");
	sleep(1);

	if (sem_post(smph))
	{
		fprintf(stdout, "FAIL\n");
		return ((void*)1);
	}
	// if (sem_post(smph))
	// {
	// 	fprintf(stdout, "FAIL\n");
	// 	return ((void*)1);
	// }
	return ((void*)0);
}

int				main(int ac, char **av)
{
	int 		i;
	pthread_t 	thread;

	char			name[50];
	i = -1;
	while (++i < PHILOS)
	{
		semanames(name, i + 1, 0);
		printf("%s\n", name);
		semanames(name, i + 1, 1);
		printf("%s\n", name);
	}

	// sem_unlink("Sema");
	// sem_close(smph);
	// if ((smph = sem_open("Sema", O_CREAT | O_EXCL, 0644, 2)) == SEM_FAILED)
	// {
	// 	printf("sem_open failed\n");
	// 	return (1);
	// }
	// i = -1;
	// while (++i < PHILOS)
	// {
	// 	pthread_create(&thread, NULL, &monitor, NULL);
	// 	pthread_detach(thread);
	// 	usleep(100000);
	// }
	// sleep(10);
	// printf("Unlink & Destroy\n");
	// sem_unlink("Sema");
	// if (sem_close(smph))
	// 	return (1);
	return (0);
}

// Soit smph open avec valeur = 1
// Si 1 sem_wait : OK on affiche toutes les 1 secondes
// Si 2 sem_wait : deadlock car aucune ressource dispo car smph < 0

// Soit smph open avec valeur = 2
// Si 1 sem_wait : Ok c'est good
// Si 2 sem_wait : PAS OK - Ca je comprends tjrs pas - Normalement c'est censé donné le meme résultat que sem init à 1 avec 1 sem_wait (1er test)
