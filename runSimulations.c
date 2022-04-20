#include <runSimulations.h>

/* Function to print the queue created. */
static void printRoad(QUEUE *left, QUEUE *right) {
	printf("\nleft: ");
	printQueue(left);
	printf("right: ");
	printQueue(right);
	printf("---\n");
}

/* Function to compile the two stats of either road into one so it can be passed back. 
   Returns the pointer to the stats. */
static RUNSTATS *compileStats(STATS *left, STATS *right) {
	RUNSTATS *compiledStats = (RUNSTATS *)malloc(sizeof(RUNSTATS));
	compiledStats->left = left;
	compiledStats->right = right;
	return compiledStats;
}

/* Runs a single run through of the simulation taking in the arrivalRate for both sides, the wait time for both sides
   and the seeded random variable to create new random numbers.
   Returns the combined stats for either side of the road. */
static RUNSTATS *runOneSimulation(double arrivalRateL, double arrivalRateR, int waitLeft, int waitRight) {
	LIGHTS 	*trafficLight 	= newLights();
	QUEUE   *left 			= NULL;
	QUEUE   *right 			= NULL;
	STATS 	*leftStats 		= newStats();
	STATS 	*rightStats 	= newStats();
	int 	i 				= 0;
	int 	a 				= 1;
	int 	wait 			= 0;
	float  random;

	for (i = 0; i < 500; i++){
		/* After a number of cars goes through, change the lights */
		if (wait >= waitLeft && trafficLight->left == 'g' || wait >= waitRight && trafficLight->right == 'g') {
			changeLights(trafficLight); 
			wait = 0;
		} else {
			/* Randomly have cars arrive on either side of the traffic lights*/
			random = 1.0*rand()/RAND_MAX;
			if (random < arrivalRateL) {
				push(&left, a);
				addTotal(leftStats);
			}
			random = 1.0*rand()/RAND_MAX;
			if (random < arrivalRateR) {
				push(&right, a);
				addTotal(rightStats);
			}
			/* If the lights on one side are green then the cars will move*/
			if ((trafficLight->left == 'g') && (left != NULL)) {
				if (left != NULL) {
					updateWaitTime(leftStats, pop(&left));
				}
			} else if ((trafficLight->right == 'g') && (right != NULL)) {
				if (right != NULL) {
					updateWaitTime(rightStats, pop(&right));
				}
			}
		}

		/* If one side of the road is green but has no cars and the otherside has cars wait, changes the lights. */
		if ((trafficLight->right == 'g' && right == NULL && left != NULL) || (trafficLight->left == 'g' && left == NULL && right != NULL)) {
			wait = waitLeft + waitRight;
		}

		/* Uncomment below for a visual representation of either side of the road (recommend use only with running one simulation) 
		   Also uncomment in the while loop too. */
		/* printRoad(left, right); */

		updateLife(left);
		updateLife(right);
		wait++;
		a++;
	}	

	/* After 500 loops this continues until all the cars have gone through with no more cars added. */
	while (left != NULL || right !=NULL) {
		/* After a number of cars goes through, change the lights */
		if (wait >= waitLeft && trafficLight->left == 'g' || wait >= waitRight && trafficLight->right == 'g') {
			changeLights(trafficLight); 
			wait = 0;
		} else {
			/* If the lights on one side are green then the cars will move*/
			if ((trafficLight->left == 'g') && (left != NULL)) {
				if (left != NULL) {
					updateWaitTime(leftStats, pop(&left));
				}
			} else if ((trafficLight->right == 'g') && (right != NULL)) {
				if (right != NULL) {
					updateWaitTime(rightStats, pop(&right));
				}
			}
		}
		/* If one side of the road is green but has no cars and the otherside has cars wait, changes the lights. */
		if (wait >= waitLeft && trafficLight->left == 'g' || wait >= waitRight && trafficLight->right == 'g') {
			changeLights(trafficLight); 
			wait = 0;
		}
		if (left != NULL) {
			leftStats->timeAfter++;
		}
		if (right != NULL) {
			rightStats->timeAfter++;
		}

		/* Uncomment below for a visual representation of either side of the road */
		/* printRoad(left, right); */

		updateLife(left);
		updateLife(right);
		wait++;
	}
	free(trafficLight);
	free(left);
	free(right);
	return compileStats(leftStats, rightStats);
}

/* Runs multiple simulations with values provided, compiles the stats produced and outputs the average values. */
static void runSimulations(float arrivalRateL, float arrivalRateR, int waitLeft, int waitRight) {
	int i;
	int carsLeft = 0;
	int carsRight = 0;
	int avgWaitLeft = 0;
	int avgWaitRight = 0;
	int maxWaitLeft = 0;
	int maxWaitRight = 0;
	int timeAfterLeft = 0;
	int timeAfterRight = 0;

	/* Adds all of the results produced from the simulations. */
	for (i = 0; i < 100; i++) {
		RUNSTATS *compiledStats = runOneSimulation(arrivalRateL, arrivalRateR, waitLeft, waitRight);
		STATS *left = compiledStats->left;
		STATS *right = compiledStats->right;
		carsLeft = carsLeft + left->cars;
		carsRight = carsRight + right->cars;
		avgWaitLeft = avgWaitLeft + (left->avgWaitTime/left->cars);
		avgWaitRight = avgWaitRight + (right->avgWaitTime/right->cars);
		maxWaitLeft = maxWaitLeft + left->maxWait;
		maxWaitRight = maxWaitRight + right->maxWait;
		timeAfterLeft = timeAfterLeft + left->timeAfter;
		timeAfterRight = timeAfterRight + right->timeAfter;
		free(compiledStats);
		free(left);
		free(right);
	}

	/* Outputs the results in a the format required. */
	printf("\nParameter values:\n"); 
	printf("%4crom left:\n", 'f');
	printf("%8craffic arrival rate: %3.2f\n", 't', arrivalRateL);
	printf("%8craffic light period:  %3d\n", 't', waitLeft);
	printf("%4crom right:\n", 'f');
	printf("%8craffic arrival rate: %3.2f\n", 't', arrivalRateR);
	printf("%8craffic light period:  %3d\n", 't', waitRight);
	printf("Results (averaged over 100 runs):\n");
	printf("%4crom left:\n", 'f');
	printf("%8cumber of vehicles:    %3d\n", 'n', carsLeft/100);
	printf("%8cverage waiting time:  %3d\n", 'a', avgWaitLeft/100);
	printf("%8caximum waiting:       %3d\n", 'm', maxWaitLeft/100);
	printf("%8clearance time:        %3d\n", 'c', timeAfterLeft/100);
	printf("%4crom right:\n", 'f');
	printf("%8cumber of vehicles:    %3d\n", 'n', carsRight/100);
	printf("%8cverage waiting time:  %3d\n", 'a', avgWaitRight/100);
	printf("%8caximum waiting:       %3d\n", 'm', maxWaitRight/100);
	printf("%8clearance time:        %3d\n\n", 'c', timeAfterRight/100);
}

int main (int argc, char *argv[]) {
	srand(time(0));
	
	if (argc == 5) {
		if (atoi(argv[3]) < 2 || atoi(argv[4]) < 2) {
			printf("Please increase the traffic light period to 2 or greater.\n");
			return 1;
		} else if (atof(argv[1]) < 1.1 || atof(argv[2]) < 1.1) {
			printf("Please decrease the traffic arrival rate to between or equal to 0 and 1 .\n");
			return 1;
		} 
		runSimulations(atof(argv[1]), atof(argv[2]), atoi(argv[3]), atoi(argv[4]));
	} else if (argc > 5) {
		printf("Too many arguments supplied.\n");
		return 1;
	} else if (argc < 5) {
		printf("Please supply 4 values for the light system to work.\n");
		return 1;
	}

	/* Uncomment below for use of one simulation. */	
	/*
	runOneSimulation(0.5, 0.5, 5, 5);
	*/
	
	return 0;
}
