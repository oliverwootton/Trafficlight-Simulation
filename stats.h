#ifndef __STATS__
#define __STATS__ 1

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/

struct roadStats {
   int cars;
   int avgWaitTime;
   int maxWait;
   int timeAfter;
};
typedef struct roadStats STATS;

/*----- function prototypes --------------------------------------------------*/

extern STATS    *newStats        ();
extern void     addTotal         (STATS *road);
extern void     updateWaitTime   (STATS *road, int life);
extern void     printStats       (STATS *road);
#endif
