#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**  
 * @brief Continuously creates threads running an idle loop to measure
 * the maximum number of threads the system can create before failure.  
 */
void	*dummy(void *arg)
{
	while (1);
	return NULL;
}

int	main(void)
{
	pthread_t tid;

	size_t count = 0;
	while (pthread_create(&tid, NULL, dummy, NULL) == 0)
	{
		count++;
		printf("Threads created: %zu\n", count);
	}
	return 0;
}
