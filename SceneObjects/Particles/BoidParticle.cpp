/*
 * BoidParticle.cpp
 *
 *  Created on: Dec 6, 2015
 *      Author: dglewis
 */

#include "BoidParticle.h"

BoidParticle::BoidParticle() {
	// TODO Auto-generated constructor stub

}

BoidParticle::~BoidParticle() {
	// TODO Auto-generated destructor stub
}


Vec3f steeringVelocity(Vec3f currentVelocity, Vec3f normal, float distance)
{
	normal.normalize();

	Vec3f projection = normal * (currentVelocity.dotProduct(normal) / normal.dotProduct(normal));
	return (currentVelocity - projection) * (1/pow(distance,2));
}

void BoidParticle::update(std::vector<Particle *> neighbours)
{
	for(Particle * p : neighbours)
	{
		if(this == p)
			continue;

		float l = (p->getPosition() - this->getPosition()).length();
		Vec3f direction = (p->getPosition() - this->getPosition());//.normalized();

		if(l <= AVOIDANCE_RADIUS)
			acceleration = acceleration + direction*AVOID_COEFFICIENT*(1./(l*l));
		else if(l <= COHESION_RADIUS)
			acceleration = acceleration + p->getVelocity() * COHESION_COEFFICIENT;
		else if(l <= MERGE_RADIUS)
			acceleration = acceleration + direction*((l*MERGE_COEFFICIENT) + 0.03);

		if(position.y() < -(float)HEIGHT/2.)
			acceleration = acceleration + Vec3f(0,10,0);
		if(position.y() > (float)HEIGHT/2.)
			acceleration = acceleration + Vec3f(0,-10,0);
		if(position.x() < -(float)WIDTH/2.)
			acceleration = acceleration + Vec3f(10,0,0);
		if(position.x() > (float)WIDTH/2.)
			acceleration = acceleration + Vec3f(-10,0,0);
		if(position.z() < -(float)DEPTH/2.)
			acceleration = acceleration + Vec3f(0,0,10);
		if(position.z() > (float)DEPTH/2.)
			acceleration = acceleration + Vec3f(0,0,-10);
	}
}

void BoidParticle::move()
{

	velocity = velocity + acceleration * DELTA_T;
	if(velocity.length() > VELOCITY_MAX)
	{
		velocity = velocity.normalized() * VELOCITY_MAX;
	}

	Vec3f deltaPos = velocity * DELTA_T;
	position = position + deltaPos;

	acceleration.x(0);
	acceleration.y(0);
	acceleration.z(0);

}
