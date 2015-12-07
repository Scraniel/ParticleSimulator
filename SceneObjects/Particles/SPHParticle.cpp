/*
 * SPHParticle.cpp
 *
 *  Created on: Nov 30, 2015
 *      Author: dglewis
 */

#include "SPHParticle.h"

SPHParticle::SPHParticle() {
	// TODO Auto-generated constructor stub
	this->velocity = Vec3f(0,0,0);
}

SPHParticle::~SPHParticle() {
	// TODO Auto-generated destructor stub
}

void SPHParticle::update(std::vector<Particle *> neighbours)
{

	//std::cout << "Inside:" << position << std::endl;
	updateDensity(neighbours);

	if(!setUp)
	{
		setUp = true;
		return;
	}
	updatePressure();


	Vec3f pressureA = pressureAcceleration(neighbours);
	Vec3f viscosityA= viscosityAcceleration(neighbours);


	acceleration = pressureA
			 + viscosityA
			 + Vec3f(0,G,0);

}

void SPHParticle::move()
{

	if(position.y() < 0)
		acceleration = acceleration + Vec3f(0,-G*5,0);
	if(position.y() > HEIGHT)
		acceleration = acceleration + Vec3f(0,G*5,0);
	if(position.x() < -(float)WIDTH/2.)
		acceleration = acceleration + Vec3f(-G*5,0,0);
	if(position.x() > (float)WIDTH/2.)
		acceleration = acceleration + Vec3f(G*5,0,0);
	if(position.z() < -(float)DEPTH/2.)
		acceleration = acceleration + Vec3f(0,0,-G*5);
	if(position.z() > (float)DEPTH/2.)
		acceleration = acceleration + Vec3f(0,0,G*5);

	velocity = velocity + acceleration * DELTA_T;
	Vec3f deltaPos = velocity * DELTA_T;
	position = position + deltaPos;


}

void SPHParticle::updateDensity(std::vector<Particle *> neighbours)
{
	float result = 0.0000000000000001;


	for(Particle * particle : neighbours)
	{

		SPHParticle * current = dynamic_cast<SPHParticle*>(particle);
		if(!current)
		{
			std::cout << "Cast did not work: updateDensity()\n";
		}
		else
			result += kernel(this->position - current->position);
	}


	density = result;

}

void SPHParticle::updatePressure()
{
	pressure = 0.01 * pow(density - 0.05, 9.0);
}

Vec3f SPHParticle::pressureAcceleration(std::vector<Particle *> neighbours)
{
	Vec3f result(0,0,0);
	for(Particle * particle : neighbours)
	{

		SPHParticle * current = dynamic_cast<SPHParticle*>(particle);
		if(!current)
		{
			std::cout << "Cast did not work: pressureAcceleration()\n";
		}
		else
		{
			Vec3f kernelInput = current->position - this->position;

			result = result +(kernelGradient(kernelInput) * (current->pressure + this->pressure) * (1./current->density));

		}

	}


	return result * (1./density);
}

Vec3f SPHParticle::viscosityAcceleration(std::vector<Particle *> neighbours)
{
	Vec3f result(0,0,0);

	for(Particle * particle : neighbours)
	{
		SPHParticle * current = dynamic_cast<SPHParticle*>(particle);
		if(!current)
		{
			std::cout << "Cast did not work: viscosityAcceleration()\n";
		}
		else
			result = result +((current->velocity - this->velocity) * (1/current->density) * 0.1 * kernel(current->position - this->position));
	}


	return result * (1/density);
}
