// Matthew Heltman 
// Sep 15 2026
//
// Entity header file 

#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
	int x; 
	int y; 

} Entity; 

void entityInit(Entity *entity); 
void printStatus(Entity *entity); 

#endif
