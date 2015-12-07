/*
 * SPHParticle.h
 *
 *  Created on: Nov 30, 2015
 *      Author: dglewis
 */

#ifndef SCENEOBJECTS_PARTICLES_SPHPARTICLE_H_
#define SCENEOBJECTS_PARTICLES_SPHPARTICLE_H_

#include "Particle.h"

class SPHParticle: public Particle {
public:
	SPHParticle();
	SPHParticle(Vec3f position) : Particle(position)
	{
		density = -1;
		pressure = 0;
		acceleration = Vec3f(0,0,0);
		velocity = Vec3f(0,0,0);
	}
	virtual ~SPHParticle();

	void update(std::vector<Particle *>); // Will always be SPHParticle
	void move();

private:
	float density, pressure;
	Vec3f acceleration;
	bool setUp = false;
	void updateDensity(std::vector<Particle *>);
	void updatePressure();
	Vec3f pressureAcceleration(std::vector<Particle *>);
	Vec3f viscosityAcceleration(std::vector<Particle *>);
};

#endif /* SCENEOBJECTS_PARTICLES_SPHPARTICLE_H_ */
