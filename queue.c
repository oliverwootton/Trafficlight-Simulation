#include <queue.h>

/*----- local function prototypes --------------------------------------------*/

static QUEUE *newNode    (int car);

/*----- QUEUE functions ------------------------------------------------------*/

/* Create a new node from the given integer and return a pointer to it */
static QUEUE *newNode (int car) {
   QUEUE *s = (QUEUE *)malloc(sizeof(QUEUE));
   if ( s==NULL ) {
      printf("Memory allocation error\n");
      exit(-1);
   }
   s->car = car;
   s->life = 0;
   s->next = NULL;
   return s;
}

/* Push a value onto the top of the QUEUE */
extern void push (QUEUE **queue, int car) {
   QUEUE   *s    = *queue;
   if (s == NULL) {
      s = newNode(car);
   } else if (s->next == NULL) {
      QUEUE   *n = newNode(car);
      s->next = n;
   } else {
      QUEUE   *n = s->next;
      push(&n, car);
   }
   *queue = s;
}

/* Pop a value off the front of the queue and return how long it was waiting */
extern int pop (QUEUE **queue) {
   QUEUE   *s    = *queue;
   int     life = 0;

   if ( s==NULL ) {
      printf("Warning: attempting to pop from an empty queue.\n");
      printf("Warning: line %d, file %s\n",__LINE__,__FILE__);
      return life;
   }
   life = s->life;
   *queue = s->next;
   free(s);
   return life;
}

/* Recursively print out the contents of the queue */
extern void printQueue (QUEUE *queue) {
   if ( queue==NULL ) {
      printf("\n");
      return;
   }
   else
   {
      printf("%d",queue->car);
      printf(", ");
      printQueue(queue->next);
   }
}

/* Recursively add 1 to the life of each value in the queue. */ 
extern void updateLife (QUEUE *queue) {
   if (queue == NULL) {
      return;
   } else {
      queue->life++;
      updateLife(queue->next);
   }
}

/* recursively empty the queue, thus freeing all the memory */
extern void emptyQueue (QUEUE **queue) {
   if ( *queue==NULL )
      return;
   else
   {
      pop(queue);
      emptyQueue(queue);
   }
}
