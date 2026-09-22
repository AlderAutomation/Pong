// Matthew Heltman 
// Sep 22 2026
//
// Ball

#ifndef BALL_H
#define BALL_H

#include "Entity.h"

typedef struct {
	Entity entity; 
	float radius; 
} Ball;

void ballInit(Ball *ball); 

#endif
