
#include "pca9685.h"

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

/* [234-410] */
int pwm = 1;
int pwm0 = 1;
int pwm1 = 1;
int pwm2 = 1;
int pwm3 = 1;

int active = 1;

void *keyboardInput(void* threadargs);

int main(void)
{
	int status = 0;
	long t;
	long NumberOfThreads = 1;
    pthread_t *threads;

	/* Setup with pinbase 300 and i2c location 0x40 */
	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		printf("Error in setup\n");
		return fd;
	}

	threads = (pthread_t *) malloc(sizeof(pthread_t) *NumberOfThreads);
    if(threads == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return -1;
    }


	for (t = 0; t < NumberOfThreads; t++) {
        printf("Creating thread %ld\n", t);
        if(pthread_create(&threads[t], NULL, keyboardInput, (void *) t)) {
          fprintf(stderr, "Thread creation failed: %s\n", strerror(errno));
          return -2;
        }
    }

	pca9685PWMReset(fd);
	pwmWrite(PIN_BASE + 16, pwm);

	while (active)
	{
		pwmWrite(PIN_BASE + 16, pwm);
	}

	for (t = 0; t < NumberOfThreads; t++) {
		printf("Main joining with thread %ld\n", t);
		if(pthread_join(threads[t],(void *) &status)) {
        	fprintf(stderr, "Join %ld failed %s\n", t, strerror(errno));
        	return -3;
    	}

    	printf("Completed joining with thread %ld status = %d\n", t,
        	    status);
	}

	pca9685PWMReset(fd);
	free(threads);
	return 0;
}

void *keyboardInput(void* threadargs) {
	char c;
	while(1) {
		c = getchar();
		if(c == '+') {
			pwm++;
			if(pwm < 234) {
				pwm = 234;			
			} else if(pwm > 410) {
				pwm = 410;
			}
		}

		if(c == '-') {
			pwm--;
			if(pwm < 234) {
				pwm = 234;
			}
		}

		if(c == '1') {

		}

		if(c == 'q') {
			active = 0;
			break;
		}
		printf("pwm: %d\n", pwm);	
	}

	pthread_exit(0);
	return NULL;
}