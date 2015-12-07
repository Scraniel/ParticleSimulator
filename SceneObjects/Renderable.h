/*
 * GLCurve.h
 *
 *  Created on: Sep 23, 2015
 *      Author: dglewis
 */

#ifndef GLCURVE_H_
#define GLCURVE_H_

#include <GL/glew.h> // include BEFORE glut
#include <GL/glut.h>
#include "../MathTools/Mat4f.h"
#include "../MathTools/OpenGLMatrixTools.h"
#include "../OpenGLTools/ShaderTools.h"
#include "../MathTools/Vec3f.h"

class Renderable {
public:
	Renderable();
	virtual ~Renderable();
	std::vector<Vec3f> getVerts();
	virtual void setVerts(std::vector<Vec3f>);
	void setVert(int, Vec3f);
	virtual std::vector<float> getColours();
	Vec3f getColour();
	void setColour(Vec3f);
	int getRenderMode();
	void setRenderMode(int);
	std::string getVertexShaderPath();
	std::string getFragmentShaderPath();
	std::string getGeometryShaderPath();
	void setVertexShaderPath(std::string);
	void setFragmentShaderPath(std::string);
	void setGeometryShaderPath(std::string);
	std::vector<int> getIndices();
	void setIndices(std::vector<int>);
	void setNormals(std::vector<Vec3f>);
	std::vector<Vec3f> getNormals();

	// Will most likely move to private, just for incremental testing
	GLuint vaoID;
	GLuint basicProgramID;

	// Could store these two in an array GLuint[]
	GLuint vertBufferID;
	GLuint colorBufferID;
	GLuint indexBufferID;
	GLuint normalBufferID;

	Mat4f M, MVP;

	bool useIndexBuffer = false;
	bool useGeometryShader = false;
	void generateIDs();
	void deleteIDs();

	std::vector<Vec3f> normals;


protected:
	// The vertices that make up the curve
	std::vector<Vec3f> verts;
	std::vector<int> indices;
	// The colour to draw the curve as
	Vec3f colour;
	int renderMode; // GLEnum that tells the GPU how to render this object, eg. GL_LINES
	std::string fragmentShaderPath, vertexShaderPath, geometryShaderPath;


};

#endif /* GLCURVE_H_ */
