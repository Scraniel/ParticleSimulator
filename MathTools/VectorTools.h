/*
 * VectorTools.h
 *
 *  Created on: Sep 25, 2015
 *      Author: dglewis
 */

#ifndef MATHTOOLS_VECTORTOOLS_H_
#define MATHTOOLS_VECTORTOOLS_H_

#include "Vec3f.h"
#include <vector>

class VectorTools {
public:

	static std::vector<Vec3f> subdivide(std::vector<Vec3f>, int);
	static Vec3f affineCombination(Vec3f, Vec3f, float);
	static double length(Vec3f);
	static std::vector<Vec3f> arcLengthReparameterize(float , std::vector<Vec3f> );
};

#endif /* MATHTOOLS_VECTORTOOLS_H_ */
