/*
 * FileHelper.cpp
 *
 *  Created on: Sep 24, 2015
 *      Author: dglewis
 */

#include "FileHelper.h"

/* Loads a curve from a ".vert" file, which is constructed as such:
 * 2				//First line is the number of vec3f's to read (call this 'n')
 * 1.0 1.0 1.0		// Second line is always the colour to render the curve
 * -1.0 1.0 0.0		// The remaining n -1 lines are the vertices of the curve
 */
void FileHelper::loadCurveFromFile(const char* file, Renderable & curve){

	char buffer[50];
	FILE* fp;
	int numPoints;

	fp = fopen(file, "r");

	fgets(buffer, 50, fp);
	numPoints = atoi(buffer);

	std::vector<Vec3f> verts;
	for(int i = 0; i < numPoints; i++){
		float temp1, temp2, temp3;
		fgets(buffer, 50, fp);
		sscanf(buffer, "%f %f %f\n", &temp1, &temp2, &temp3);
		Vec3f vert(temp1, temp2, temp3);

		// First point is the colour
		if(i == 0)
		{
			curve.setColour(vert);
		}

		// Remaining points are the vertices
		else
		{
			verts.push_back(vert);
		}

	}

	curve.setVerts(verts);

	fclose(fp);
	printf("Loaded %s!\n", file);
}

