/*
 * ParticleSystem.h
 *
 *  Created on: Nov 28, 2015
 *      Author: dglewis
 */

#ifndef SCENEOBJECTS_PARTICLESYSTEM_H_
#define SCENEOBJECTS_PARTICLESYSTEM_H_

#include "Renderable.h"
#include "Particles/Particle.h"
#include <algorithm>
#include "Constants.h"

class ParticleSystem: public Renderable {
public:
	ParticleSystem();
	virtual ~ParticleSystem();
	void update();
	void freePointers();
	void setParticles(std::vector<Particle*>);
	std::vector<Particle*> getParticles();
	void fillVoxels();


private:
	std::vector<Particle*> particles;
	std::vector<Particle*> buffer;
	ParticleHolder voxels[X_DIVISIONS][Y_DIVISIONS][Z_DIVISIONS];
	unsigned long currentTime = 0;

	void getNeighbours(Particle *, int &, int &, int &);
	double Normalize(const double &, const double &, const double &, const double &, const double &);
	void updateVoxel(Particle * p);
	inline float clamp(float x, float a, float b)
	{
	    return x < a ? a : (x > b ? b : x);
	}
};

#endif /* SCENEOBJECTS_PARTICLESYSTEM_H_ */
