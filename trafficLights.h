#ifndef __TRAFFICLIGHTS__
#define __TRAFFICLIGHTS__ 1

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/
struct trafficLights {
   char left;
   char right;
};
typedef struct trafficLights LIGHTS;

/*----- function prototypes --------------------------------------------------*/

extern LIGHTS  *newLights     ();
extern void    changeLights   ();
#endif
