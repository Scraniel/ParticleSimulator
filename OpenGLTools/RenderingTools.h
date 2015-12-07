/*
 * RenderingTools.h
 *
 *  Created on: Nov 5, 2015
 *      Author: dglewis
 */

#ifndef OPENGLTOOLS_RENDERINGTOOLS_H_
#define OPENGLTOOLS_RENDERINGTOOLS_H_

#include<GL/glew.h> // include BEFORE glut
#include<GL/glut.h>

#include "../SceneObjects/Renderable.h"

class RenderingTools {
public:
	static void reloadMVPUniform(Renderable&);
	static void setupVAO(Renderable&);
	static void loadBuffer(Renderable&);
	static void loadIndexBuffer(Renderable&);
};

#endif /* OPENGLTOOLS_RENDERINGTOOLS_H_ */
