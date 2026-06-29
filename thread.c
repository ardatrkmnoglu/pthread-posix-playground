#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define ITER 1000000

static unsigned long long int shared_counter = 0;
pthread_mutex_t counter_mutex;

void* increment_counter(void* arg) {
	char* thread_name = (char*)arg;

	for (int i = 0; i < ITER; i++) {

		/*---------- critical section ----------*/

		pthread_mutex_lock(&counter_mutex);
		shared_counter++;
		pthread_mutex_unlock(&counter_mutex);

		/*-------- end critical section --------*/

	}
	printf("Loop complete: %s\n", thread_name);
	return NULL;
}


int main() {
	pthread_t thread1, thread2, thread3;

	if (pthread_mutex_init(&counter_mutex, NULL) != 0) return 1;

	pthread_create(&thread1, NULL, increment_counter, "Thread 1");
	pthread_create(&thread2, NULL, increment_counter, "Thread 2");
	pthread_create(&thread3, NULL, increment_counter, "Thread 3");

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	pthread_mutex_destroy(&counter_mutex);

	printf("\n--- Results ---\n");
	printf("Expected count: %d\n", ITER * 3);
	printf("Actual count:   %lld\n", shared_counter);

	return 0;
}
