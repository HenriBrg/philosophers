#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NTHREADS 4

long 				global=0;
pthread_mutex_t		mutex_global;

int increment(int i)
{
  return (i+1);
}

void 	*func(void * param)
{
	int	err;

	//sleep(5);
	for (int j = 0; j<500000; j++)
  	{
		// Très intéressant ce printf : s'affiche autant de fois qu'il y a de thread
		// printf("before locking\n");
		err = pthread_mutex_lock(&mutex_global);
		if (err != 0)
			fprintf(stderr,"pthread_mutex_lock");
		global=increment(global);
		err = pthread_mutex_unlock(&mutex_global);
		if (err != 0)
			fprintf(stderr,"pthread_mutex_unlock");
  	}
	return (NULL);
}

int main (int argc, char **argv)
{
	int err;
	pthread_t thread[NTHREADS];

	err = pthread_mutex_init( &mutex_global, NULL);
	if (err != 0)
		fprintf(stderr, "pthread_mutex_init");
	for (int i = 0; i < NTHREADS ; i++)
	{
		err = pthread_create(&(thread[i]), NULL, &func, NULL);
		if (err != 0)
			fprintf(stderr,"pthread_create");
	}
	for(int i = 0; i < 1000000000; i++);
	for(int i = NTHREADS-1; i >= 0; i--)
	{
		err = pthread_join(thread[i], NULL);

		printf("Hello\n");

		if(err != 0)
			fprintf(stderr,"pthread_join");
	}
	err = pthread_mutex_destroy(&mutex_global);
	if(err != 0)
    	fprintf(stderr,"pthread_mutex_destroy");
	printf("global: %ld\n",global);
	return(EXIT_SUCCESS);
}
