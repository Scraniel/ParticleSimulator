/*
 * ParticleSystem.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: dglewis
 */

#include "ParticleSystem.h"
#include "Particles/SPHParticle.h"
#include <unordered_set>

ParticleSystem::ParticleSystem() {
	// TODO Auto-generated constructor stub
	this->fragmentShaderPath = "Shaders/basic_fs.glsl";
	this->vertexShaderPath = "Shaders/basic_vs.glsl";
	this->colour = Vec3f(1,0,0);
	this->renderMode = GL_POINTS;
}

ParticleSystem::~ParticleSystem() {
	// TODO Auto-generated destructor stub
}

void ParticleSystem::update()
{
	int startX, startY, startZ;

	for(int i = 0; i < particles.size(); i++)
	{
		Particle* current = particles[i];

		getNeighbours(current, startX, startY, startZ);


		current->update(particles);
		current->move();
	}
	currentTime++;

	fillVoxels();
	this->setParticles(particles);

}

std::vector<Particle*> ParticleSystem::getParticles()
{
	return particles;
}

void ParticleSystem::setParticles(std::vector<Particle*> particles)
{
	this->particles = particles;

	std::vector<Vec3f> newVerts;
	for(Particle * p : particles)
	{
		newVerts.push_back(p->getPosition());
	}

	this->verts = newVerts;
}

void ParticleSystem::freePointers()
{
	for(Particle * p : particles)
	{
		delete p;
	}
}

// For initially filling the voxels
void ParticleSystem::fillVoxels()
{

	for(Particle * p : particles)
	{
		updateVoxel(p);
	}
}

void ParticleSystem::updateVoxel(Particle * p)
{
	int xIndex, yIndex, zIndex;
	double xCurrent, yCurrent, zCurrent;
	Vec3f currentPos;

	currentPos = p->getPosition();

	xCurrent = Normalize(currentPos.x(), -((float)WIDTH)/2., ((float)WIDTH)/2., 0, WIDTH);
	yCurrent = currentPos.y(); // y is normalized already
	zCurrent = Normalize(currentPos.z(), -((float)DEPTH)/2., ((float)DEPTH)/2., 0, DEPTH);

	xIndex = clamp(( xCurrent / (float)WIDTH) * X_DIVISIONS,0,X_DIVISIONS - 1);
	yIndex = clamp((yCurrent / (float)HEIGHT) * Y_DIVISIONS,0,Y_DIVISIONS - 1);
	zIndex = clamp((zCurrent / (float)DEPTH) * Z_DIVISIONS, 0,Z_DIVISIONS - 1);

	if(voxels[xIndex][yIndex][zIndex].lastAccessed() < currentTime)
	{
		voxels[xIndex][yIndex][zIndex].particles.clear();
		voxels[xIndex][yIndex][zIndex].update(currentTime);
	}

	voxels[xIndex][yIndex][zIndex].push_back(p);
}

void ParticleSystem::getNeighbours(Particle * particle, int & startX, int & startY, int & startZ)
{

	buffer.clear();

	int xIndex, yIndex, zIndex, xBound, yBound, zBound;
	Vec3f currentPos = particle->getPosition();

	float xCurrent = Normalize(currentPos.x(), -((float)WIDTH)/2., ((float)WIDTH)/2., 0, WIDTH);
	float yCurrent = currentPos.y(); // y is normalized already
	float zCurrent = Normalize(currentPos.z(), -((float)DEPTH)/2., ((float)DEPTH)/2., 0, DEPTH);

	xIndex = clamp(( xCurrent / (float)WIDTH) * X_DIVISIONS,0,X_DIVISIONS - 1);
	yIndex = clamp((yCurrent / (float)HEIGHT) * Y_DIVISIONS,0,Y_DIVISIONS - 1);
	zIndex = clamp((zCurrent / (float)DEPTH) * Z_DIVISIONS, 0,Z_DIVISIONS - 1);


	startX = std::max(0, xIndex - MAX_DISTANCE);
	startY = std::max(0, yIndex - MAX_DISTANCE);
	startZ = std::max(0, zIndex - MAX_DISTANCE);

	xBound = std::min(X_DIVISIONS, startX + MAX_DISTANCE*2);
	yBound = std::min(Y_DIVISIONS, startY + MAX_DISTANCE*2);
	zBound = std::min(Z_DIVISIONS, startZ + MAX_DISTANCE*2);

	for(int i = startX; i < xBound; i++)
	{
		for(int j = startY; j < yBound; j++)
		{
			for(int k = startZ; k < zBound; k++)
			{
				if(voxels[i][j][k].lastAccessed() == currentTime)
					for(Particle * p : voxels[i][j][k].particles)
					{
						buffer.push_back(p);
					}

			}
		}
	}

}

double ParticleSystem::Normalize(const double & value, const double & oldMin, const double & oldMax, const double & newMin, const double & newMax)
{
	double a = (newMax - newMin) / (oldMax - oldMin);
	double b = newMax - a * oldMax;

	return a * value + b;
}

