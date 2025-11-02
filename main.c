#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>

#include "kurth4cker.h"

#define NTHREADS	8

void *thread_proc(void *arg) {
	printf("Thread PID: %jd\n", (intmax_t)gettid());

	sleep(120);

	return NULL;
}

int main(void) {
	int result;
	pthread_t tids[NTHREADS];

	for (int i = 0; i < NTHREADS; i++) {
		if ((result = pthread_create(&tids[i], NULL, thread_proc, NULL)) != 0) {
			fprintf(stderr, "pthread_create: %s\n", strerror(result));
			exit(EXIT_FAILURE);
		}
	}

	int fd;
	if ((fd = open("kurth4cker-driver", O_RDONLY)) == -1) {
		fprintf(stderr, "open: %s\n", strerror(result));
		exit(EXIT_FAILURE);
	}

	if (ioctl(fd, IOC_KURTH4CKER) == -1) {
		fprintf(stderr, "ioctl: %s\n", strerror(result));
		exit(EXIT_FAILURE);
	}

	close(fd);

	for (int i = 0; i < NTHREADS; i++) {
		pthread_join(tids[i], NULL);
	}

	return 0;
}
