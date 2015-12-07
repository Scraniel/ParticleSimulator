/*
 * RenderingTools.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: dglewis
 */

#include "RenderingTools.h"

void RenderingTools::reloadMVPUniform(Renderable& toLoad)
{
	GLint mvpID = glGetUniformLocation( toLoad.basicProgramID, "MVP" );

	glUseProgram( toLoad.basicProgramID );
	glUniformMatrix4fv( 	mvpID,		// ID
				1,		// only 1 matrix
				GL_TRUE,	// transpose matrix, Mat4f is row major
				toLoad.MVP.data()	// pointer to data in Mat4f
			);

	GLint mID = glGetUniformLocation( toLoad.basicProgramID, "M" );

	glUseProgram( toLoad.basicProgramID );
	glUniformMatrix4fv( 	mID,		// ID
				1,		// only 1 matrix
				GL_TRUE,	// transpose matrix, Mat4f is row major
				toLoad.M.data()	// pointer to data in Mat4f
			);

	GLint vID = glGetUniformLocation( toLoad.basicProgramID, "V" );

	glUseProgram( toLoad.basicProgramID );
	glUniformMatrix4fv( 	vID,		// ID
				1,		// only 1 matrix
				GL_TRUE,	// transpose matrix, Mat4f is row major
				IdentityMatrix().data()	// pointer to data in Mat4f
	);
}

void RenderingTools::setupVAO(Renderable& toRender)
{
	glBindVertexArray( toRender.vaoID );

	glEnableVertexAttribArray( 0 ); // match layout # in shader
	glBindBuffer( GL_ARRAY_BUFFER, toRender.vertBufferID );
	glVertexAttribPointer(
		0,		// attribute layout # above
		3,		// # of components (ie XYZ )
		GL_FLOAT,	// type of components
		GL_FALSE,	// need to be normalized?
		0,		// stride
		(void*)0	// array buffer offset
	);

	glEnableVertexAttribArray( 1 ); // match layout # in shader
	glBindBuffer( GL_ARRAY_BUFFER, toRender.colorBufferID );
	glVertexAttribPointer(
		1,		// attribute layout # above
		3,		// # of components (ie XYZ )
		GL_FLOAT,	// type of components
		GL_FALSE,	// need to be normalized?
		0,		// stride
		(void*)0	// array buffer offset
	);

	if(toRender.useIndexBuffer)
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, toRender.indexBufferID);
	}

	glBindVertexArray( 0 ); // reset to default
}

// Right now just does a solid colour
void RenderingTools::loadBuffer(Renderable& toLoad)
{

	glBindBuffer( GL_ARRAY_BUFFER, toLoad.vertBufferID );
	glBufferData(	GL_ARRAY_BUFFER,
			sizeof(Vec3f)*toLoad.getVerts().size(),	// byte size of Vec3f, 4 of them
			toLoad.getVerts().data(),		// pointer (Vec3f*) to contents of verts
			GL_DYNAMIC_DRAW );	// Usage pattern of GPU buffer

	std::vector<float> colours = toLoad.getColours();

	glBindBuffer( GL_ARRAY_BUFFER, toLoad.colorBufferID );
	glBufferData(	GL_ARRAY_BUFFER,
			sizeof(float)*colours.size(),
			colours.data(),
			GL_DYNAMIC_DRAW );
}

void RenderingTools::loadIndexBuffer(Renderable& toLoad)
{
	  // but this is only needed once here
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, toLoad.indexBufferID);
	  glBufferData(
	      GL_ELEMENT_ARRAY_BUFFER,
	      sizeof(int) *
	          toLoad.getIndices().size(), // byte size of Vec3f, 4 of them
	      toLoad.getIndices().data(),      // pointer (Vec3f*) to contents of verts
	      GL_STATIC_DRAW);                  // Usage pattern of GPU buffer

}


