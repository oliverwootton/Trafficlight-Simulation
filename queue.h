#ifndef __QUEUE__
#define __QUEUE__ 1

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/

struct queueStruct {
   int                    car;
   int                   life;
   struct queueStruct   *next;
};
typedef struct queueStruct QUEUE;

/*----- function prototypes --------------------------------------------------*/

extern void   push       (QUEUE **, int);
extern int    pop        (QUEUE **);
extern void   printQueue (QUEUE *);
extern void   updateLife (QUEUE *queue);
extern void   emptyQueue (QUEUE **);
#endif
