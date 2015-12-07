/*
 * VectorTools.cpp
 *
 *  Created on: Sep 25, 2015
 *      Author: dglewis
 */

#include "VectorTools.h"

/*
 * Creates a subdivision curve (Chaikin) using the 'Chasing Game' algorithm.
 * NOTE: Does not move the first or last points in the curve.
 *
 * points: the points that create the initial curve to subdivide.
 * depth: how many iterations to subdivide. Higher depth = more points, smoother curve.
 *
 * Returns:
 * A vector containing the new points representing the subdivided curve.
 */
std::vector<Vec3f> VectorTools::subdivide(std::vector<Vec3f> points, int depth)
{
	if(depth == 0)
	{
		return points;
	}

	std::vector<Vec3f> newPoints;

	// For each pair of points, we create a new point halfway between them
	for(unsigned int i = 0; i < points.size(); i++)
	{
		Vec3f firstPoint = points.at(i);
		Vec3f secondPoint = points.at((i+1)%points.size());

		Vec3f inBetweenPoint = affineCombination(firstPoint, secondPoint, 0.5);

		// Move each point halfway towards its new neighbour
		firstPoint = affineCombination(firstPoint, inBetweenPoint, 0.5);
		inBetweenPoint = affineCombination(inBetweenPoint, secondPoint, 0.5);


		newPoints.push_back(firstPoint);

		newPoints.push_back(inBetweenPoint);
	}

	return subdivide(newPoints, depth - 1);

}

/*
 * Returns and affine combination of the two points given a proportion.
 * ie. Moves firstPoint a proportion of the way towards secondPoint.
 *
 * TODO: Move into one of the math helper classes?
 */
Vec3f VectorTools::affineCombination(Vec3f firstPoint, Vec3f secondPoint, float proportion)
{
	return firstPoint + ((secondPoint - firstPoint) * proportion);
}

double VectorTools::length(Vec3f direction)
{
	return sqrt(pow(direction.x(), 2) + pow(direction.y(), 2) + pow(direction.z(), 2));
}

// Fixes a curve so that it's points are all a fixed distance from one another.
// In other words, splits the track into 'factor' pieces.
// NOTE: factor should be larger than the number of vertices in the original curve
std::vector<Vec3f> VectorTools::arcLengthReparameterize(float factor, std::vector<Vec3f> curve)
{
	/*
	if(factor < curve.size())
	{
		std::cerr << "ERROR: The factor chosen: " << factor << ", is smaller than the number of vertices in the curve: " << curve.size() <<"\n";
		return curve;
	}
*/
	// find the length of the curve (TODO: move into track (and create a track class))
	float total = 0;
	for(unsigned int i = 0; i < curve.size()-1; i++)
	{
		 Vec3f previous = curve.at(i);
		 Vec3f next = curve.at(i+1);

		 total += (next - previous).length();
	}

	float distance = total / factor;

	std::vector<Vec3f> reparameterizedCurve;
	Vec3f currentPosition = curve.at(0);
	reparameterizedCurve.push_back(currentPosition);
	bool endOfCurve = false;
	unsigned int previousIndex = 0;
	while(previousIndex < curve.size() - 1)
	{

		unsigned int nextIndex = previousIndex + 1;
		Vec3f previousPoint = curve.at(previousIndex);

		Vec3f nextPoint = curve.at(nextIndex);
		Vec3f toGo;
		Vec3f previousToNext = nextPoint - previousPoint;
		float distanceTravelled = (nextPoint - currentPosition).length();

		// We are on the correct line segment
		if( distanceTravelled >= distance)
		{
			toGo = (previousToNext * (1.0f/previousToNext.length())) * distance;
			currentPosition = currentPosition + toGo;
			reparameterizedCurve.push_back(currentPosition);
		}
		// We're not on the correct line segment; find it!

		else
		{

			// Look through each segment until we've accumulated enough distance
			do
			{
				previousIndex = nextIndex;
				nextIndex = nextIndex + 1;

				if(nextIndex >= curve.size())
				{
					endOfCurve = true;
					break;
				}
				previousPoint = curve.at(previousIndex);
				nextPoint = curve.at(nextIndex);
				previousToNext = nextPoint - previousPoint;

				distanceTravelled +=  previousToNext.length();


			}while(distanceTravelled < distance);

			if(!endOfCurve){
				// This is necessary because we need to know how much distance was traversed
				// on every line segment BUT the one we're on
				distanceTravelled -= previousToNext.length();

				// We've found the right segment!
				// Our new position is some percentage along this segment. To find that percentage,
				// subtract how far we went on every line segment BUT this one from how far we want to go
				// (which gives us how much further we need to go) and divide it by the length of the
				// current segment
				currentPosition = previousPoint + (previousToNext * (1.0f/previousToNext.length())) * (distance - distanceTravelled);


				reparameterizedCurve.push_back(currentPosition);
			}
		}
	}
	return reparameterizedCurve;
}
