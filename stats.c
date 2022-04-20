#include <stats.h>

/* Creates a new blank set of sets and returns the pointer. */
extern STATS *newStats() {
	STATS *road = (STATS *)malloc(sizeof(STATS));
	road->cars = 0;
	road->avgWaitTime = 0;
	road->maxWait = 0;
	road->timeAfter = 0;
	return road;
}

/* Adds 1 to the number of cars. */ 
extern void addTotal(STATS *road) {
    road->cars++;
}

/* Updates the values of average and max wait time. */
extern void updateWaitTime(STATS *road, int life) {
	if (life != 0 ) {
		road->avgWaitTime = (road->avgWaitTime + life);

		if (road->maxWait < life) {
			road->maxWait = life;
		}
	}
}

/* Prints the stats for one side of the road. */
extern void printStats(STATS *road) {
	printf("The total number of cars: %d\n", road->cars);
	printf("The average wait time: %d\n", road->avgWaitTime/road->cars);
	printf("The max wait time: %d\n", road->maxWait);
	printf("The time after taken to finish: %d\n", road->timeAfter);
	printf("\n");
}
