#include <trafficLights.h>

/* Creates the two traffic lights and returns the pointer to them. */ 
extern LIGHTS *newLights() {
	LIGHTS *l = (LIGHTS *)malloc(sizeof(LIGHTS));
	if (l == NULL) {
		printf("Memory allocation error\n");
		exit(-1);
	}
	l->left = 'r';
	l->right = 'g';
	return l;
}

/* Swaps the green light over making sure they cannot be equal */
extern void changeLights(LIGHTS *lights) {
	if (lights->right == 'r') {
		lights->right = 'g'; 
		lights->left = 'r'; 
	} else {
		lights->right = 'r'; 
		lights->left = 'g';  
	}
}
