// Matthew Heltman 
// Sep 22 2026
//
// Ball

#ifndef BALL_H
#define BALL_H

#include <stdbool.h>

#include "Entity.h"

typedef struct {
	Entity entity; 
	float radius; 
	float speedX; 
	float speedY; 
} Ball;

void ballInit(Ball *ball); 
void moveBall(Ball *ball); 
void bounceBall(Ball *ball); 


#endif
