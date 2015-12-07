/*
 * GLCurve.cpp
 *
 *  Created on: Sep 23, 2015
 *      Author: dglewis
 */

#include "Renderable.h"

Renderable::Renderable() {
	// TODO Auto-generated constructor stub
	MVP = IdentityMatrix();
	M = IdentityMatrix();

}

Renderable::~Renderable() {
	// TODO Auto-generated destructor stub
}


std::vector<Vec3f> Renderable::getVerts()
{
	return verts;
}

void Renderable::setVerts(std::vector<Vec3f> newVerts)
{
	verts = newVerts;
}

std::vector<float> Renderable::getColours()
{
	std::vector<float> colours;

	for(unsigned int i = 0; i < verts.size(); i++)
	{
		colours.push_back(colour.x());
		colours.push_back(colour.y());
		colours.push_back(colour.z());
	}

	return colours;
}

Vec3f Renderable::getColour()
{
	return colour;
}

void Renderable::setColour(Vec3f newColour)
{
	colour = newColour;
}

void Renderable::setRenderMode(int newRenderMode)
{
	renderMode = newRenderMode;
}

int Renderable::getRenderMode()
{
	return renderMode;
}

void Renderable::setVertexShaderPath(std::string newVertexShaderPath)
{
	vertexShaderPath = newVertexShaderPath;
}

std::string Renderable::getVertexShaderPath()
{
	return vertexShaderPath;
}

void Renderable::setFragmentShaderPath(std::string newfragmentShaderPath)
{
	fragmentShaderPath = newfragmentShaderPath;
}

std::string Renderable::getFragmentShaderPath()
{
	return fragmentShaderPath;
}

void Renderable::setGeometryShaderPath(std::string newGeometryShaderPath)
{
	geometryShaderPath = newGeometryShaderPath;
}

std::string Renderable::getGeometryShaderPath()
{
	return geometryShaderPath;
}

std::vector<int> Renderable::getIndices()
{
	return this->indices;
}

void Renderable::setIndices(std::vector<int> newIndices)
{
	this->indices = newIndices;
}

void Renderable::setNormals(std::vector<Vec3f> newNormals)
{
	this->normals = newNormals;
}

std::vector<Vec3f> Renderable::getNormals()
{
	return this->normals;
}

void Renderable::generateIDs()
{
	std::string vsSource = loadShaderStringfromFile( vertexShaderPath );
	std::string fsSource = loadShaderStringfromFile( fragmentShaderPath );
	if(useGeometryShader)
	{
		std::string gsSource = loadShaderStringfromFile(geometryShaderPath);
		basicProgramID = CreateShaderProgram( vsSource, gsSource, fsSource );
	}
	else
		basicProgramID = CreateShaderProgram( vsSource, fsSource );

	// load IDs given from OpenGL
	glGenVertexArrays( 1, &vaoID );
	glGenBuffers( 1, &vertBufferID );
	glGenBuffers( 1, &colorBufferID );
	if(this->useIndexBuffer)
		glGenBuffers(1, &indexBufferID);
}

void Renderable::deleteIDs()
{
	glDeleteProgram( basicProgramID );
	glDeleteVertexArrays( 1, &vaoID );
	glDeleteBuffers( 1, &vertBufferID );
	glDeleteBuffers( 1, &colorBufferID );
	if(this->useIndexBuffer)
			glDeleteBuffers(1, &indexBufferID);
}

void Renderable::setVert(int index, Vec3f newVert)
{
	if(index >= verts.size())
	{
		std::cerr << "ERROR: Index " << index << " outside of range. Cannot update vertex.";
		return;
	}

	verts.at(index) = newVert;

}
