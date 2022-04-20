#ifndef __RUNSIMULATIONS__
#define __RUNSIMULATIONS__ 1

#include <queue.h>
#include <trafficLights.h>
#include <stats.h>

/*----- structure definition -------------------------------------------------*/

struct statsForRun {
   STATS *left;
   STATS *right;
};
typedef struct statsForRun RUNSTATS;

/*----- function prototypes --------------------------------------------------*/

static void       printRoad            (QUEUE *left, QUEUE *right);
static RUNSTATS   *compileStats        (STATS *left, STATS *right);
static RUNSTATS   *runOneSimulation    (double randL, double randR, int lightsLeft, int lightsRight);
static void       runSimulations       (float randL, float randR, int waitLeft, int waitRight);
#endif
