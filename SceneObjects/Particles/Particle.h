/*
 * Particle.h
 *
 *  Created on: Nov 28, 2015
 *      Author: dglewis
 */

#ifndef SCENEOBJECTS_PARTICLE_H_
#define SCENEOBJECTS_PARTICLE_H_

#include "../../MathTools/Vec3f.h"
#include <stdlib.h>
#include "../Constants.h"

extern float DELTA_T;
extern float SIGMA;
extern float G;
extern int WIDTH, HEIGHT, DEPTH;

struct ParticleHolder;

class Particle {
public:
	Particle();
	Particle(Vec3f);
	virtual void update(std::vector<Particle*>);
	virtual void move();
	void setPosition(Vec3f);
	Vec3f getPosition();
	Vec3f getVelocity();

protected:
	Vec3f position, velocity;
	float kernel(Vec3f);
	Vec3f kernelGradient(Vec3f);
};

struct ParticleHolder
{
public:
	std::vector<Particle *> particles;
	unsigned long currentTime = 0;
	void push_back(Particle *);
	unsigned long lastAccessed();
	void update(unsigned long);

};

#endif /* SCENEOBJECTS_PARTICLE_H_ */
