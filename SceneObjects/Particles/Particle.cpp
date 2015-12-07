/*
 * Particle.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: dglewis
 */

#include "Particle.h"

float DELTA_T = 0.5;
float SIGMA = .65;

float G = -0.003;
int WIDTH = 4;
int HEIGHT = 4;
int DEPTH = 4;
#define SIGMA2 (SIGMA * SIGMA)
#define SQRT_2_PI 2.5066282746310005
#define DENOMINATOR std::pow(SIGMA*SQRT_2_PI, 3)

Particle::Particle()
{
	this->velocity = Vec3f(((double) rand() / (RAND_MAX)),((double) rand() / (RAND_MAX)),0);
}

Particle::Particle(Vec3f position)
{
	this->position = position;
}


void Particle::update(std::vector<Particle *>)
{
	// Update Velocity


}
void Particle::move()
{
	setPosition(getPosition() + (getVelocity() * DELTA_T * 100));
}


void Particle::setPosition(Vec3f position)
{
	this->position = position;
}

Vec3f Particle::getPosition()
{
	return this->position;
}

Vec3f Particle::getVelocity()
{
	return this->velocity;
}

float Particle::kernel(Vec3f position)
{

	float denominator = (2.0 * SIGMA2);
	float x2 = position.x() * position.x();
	float y2 = position.y() * position.y();
	float z2 = position.z() * position.z();
	float normalizedDistanceSquared = ( x2 + y2 + z2)/denominator;

	if(normalizedDistanceSquared >= 50)
		return 0;

	return (1./DENOMINATOR) * exp(-normalizedDistanceSquared);
}

Vec3f Particle::kernelGradient(Vec3f position)
{

	return ((position * -1.) * (1./(SIGMA2))) * kernel(position);
}

void ParticleHolder::push_back(Particle * newParticle)
{
	particles.push_back(newParticle);
}

unsigned long ParticleHolder::lastAccessed()
{
	return currentTime;
}

void ParticleHolder::update(unsigned long newTime)
{
	currentTime = newTime;
}
