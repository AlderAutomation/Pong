// Matthew Heltman 
// Sept 15 
//
// Entity class for ball and paddle parent 


#include <stdio.h>

#include "Entity.h"

void entityInit(Entity *entity) {
	entity->x = 0; 
	entity->y = 0;
}

void printStatus(Entity *entity) {
	printf("POS X: %i\nPOS Y: %i\n", entity->x, entity->y); 

}

