/*
 * BoidParticle.h
 *
 *  Created on: Dec 6, 2015
 *      Author: dglewis
 */

#ifndef SCENEOBJECTS_PARTICLES_BOIDPARTICLE_H_
#define SCENEOBJECTS_PARTICLES_BOIDPARTICLE_H_

#include "Particle.h"

class BoidParticle: public Particle {
public:
	BoidParticle();
	BoidParticle(Vec3f position) : Particle(position)
	{
		acceleration = Vec3f(0,0,0);
		velocity = Vec3f(((float)std::rand()/RAND_MAX) * 0.05,((float)std::rand()/RAND_MAX) * 0.05,((float)std::rand()/RAND_MAX) * 0.05);
	}
	virtual ~BoidParticle();

	void update(std::vector<Particle*>);
	void move();

private:
	Vec3f acceleration;
	static constexpr float AVOIDANCE_RADIUS =0.2;
	static constexpr float COHESION_RADIUS = 0.3;
	static constexpr float MERGE_RADIUS = 0.5;
	static constexpr float VELOCITY_MAX = 0.05;
	static constexpr float AVOID_COEFFICIENT = -0.7;
	static constexpr float COHESION_COEFFICIENT = 0.3;
	static constexpr float MERGE_COEFFICIENT = 1;
};

#endif /* SCENEOBJECTS_PARTICLES_BOIDPARTICLE_H_ */
