// CPSC 587 Created By: Andrew Owens
// This is a (very) basic program to
// 1) load shaders from external files, and make a shader program
// 2) make Vertex Array Object and Vertex Buffer Object for the triangle

// take a look at the following sites for further readings:
// opengl-tutorial.org -> The first triangle (New OpenGL, great start)
// antongerdelan.net -> shaders pipeline explained
// ogldev.atspace.co.uk -> good resource 


// NOTE: this dependencies (include/library files) will need to be tweaked if
// you wish to run this on a non lab computer

#include<iostream>
#include<cmath>

#include<GL/glew.h> // include BEFORE glut
#include<GL/glut.h>

#include "MathTools/Mat4f.h"
#include "MathTools/OpenGLMatrixTools.h"
#include "MathTools/Vec3f.h"
#include "MathTools/VectorTools.h"
#include "Helpers/FileHelper.h"
#include "OpenGLTools/ShaderTools.h"
#include "OpenGLTools/RenderingTools.h"
#include "SceneObjects/Renderable.h"
#include "SceneObjects/ParticleSystem.h"
#include "SceneObjects/Particles/SPHParticle.h"
#include "SceneObjects/Particles/BoidParticle.h"


using std::cout;
using std::endl;
using std::cerr;

Mat4f MVP;
Mat4f M; // Every model should have it's own Model matrix
Mat4f V;
Mat4f P;

float thetaYRotate = 0;
float thetaXRotate = 0;
float mousePreviousX = 0;
float mousePreviousY = 0;

ParticleSystem particleSystem;
Renderable bounds;
std::vector<Renderable*> toRender = {&particleSystem, &bounds};

int WIN_WIDTH = 800, WIN_HEIGHT = 600;

// function declarations... just to keep things kinda organized.
void displayFunc();
void resizeFunc(int, int);
void idleFunc();
void init();
void loadProjectionMatrix();
void loadModelViewMatrix();
void setupModelViewProjectionTransform();
int main( int, char** );
void mouseButtonFunc( int button, int state, int x, int y);
void reloadMVPUniformAllObjects();
// function declarations

void mouseButtonFunc( int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		particleSystem.update();
}

void setupBounds()
{
	Vec3f topLeftFront = Vec3f(-WIDTH/2., HEIGHT/2.,DEPTH/2.);
	Vec3f topLeftBack = Vec3f(-WIDTH/2., HEIGHT/2.,-DEPTH/2.);
	Vec3f topRightFront = Vec3f(WIDTH/2., HEIGHT/2.,DEPTH/2.);
	Vec3f topRightBack = Vec3f(WIDTH/2., HEIGHT/2.,-DEPTH/2.);
	Vec3f botLeftFront = Vec3f(-WIDTH/2., -HEIGHT/2.,DEPTH/2.);
	Vec3f botLeftBack = Vec3f(-WIDTH/2., -HEIGHT/2.,-DEPTH/2.);
	Vec3f botRightFront = Vec3f(WIDTH/2., -HEIGHT/2.,DEPTH/2.);
	Vec3f botRightBack = Vec3f(WIDTH/2., -HEIGHT/2.,-DEPTH/2.);


	bounds.setColour(Vec3f(0,0,1));
	bounds.setFragmentShaderPath("Shaders/basic_fs.glsl");
	bounds.setVertexShaderPath("Shaders/basic_vs.glsl");
	bounds.setRenderMode(GL_LINES);
	std::vector<Vec3f> points;

	points.push_back(topLeftFront);
	points.push_back(topLeftBack);

	points.push_back(topLeftBack);
	points.push_back(topRightBack);

	points.push_back(topRightBack);
	points.push_back(topRightFront);

	points.push_back(topRightFront);
	points.push_back(topLeftFront);

	points.push_back(botLeftFront);
	points.push_back(botLeftBack);

	points.push_back(botLeftBack);
	points.push_back(botRightBack);

	points.push_back(botRightBack);
	points.push_back(botRightFront);

	points.push_back(botRightFront);
	points.push_back(botLeftFront);

	points.push_back(topLeftFront);
	points.push_back(botLeftFront);

	points.push_back(topRightFront);
	points.push_back(botRightFront);

	points.push_back(topLeftBack);
	points.push_back(botLeftBack);

	points.push_back(topRightBack);
	points.push_back(botRightBack);



	bounds.setVerts(points);
}


void mouseMotionFunc(int x, int y)
{

	thetaYRotate = ((x - mousePreviousX) / WIN_WIDTH) * 360; // May not be necessary
	mousePreviousY = y;
	mousePreviousX = x;

	for(unsigned int i = 0; i < toRender.size(); i++)
	{
		Renderable & current = *toRender.at(i);
		current.M = current.M * RotateAboutYMatrix( thetaYRotate );
	}

	setupModelViewProjectionTransform();
	reloadMVPUniformAllObjects();
}

// Reloads the MVP uniform for all objects in the scene, and calls for a redisplay
void reloadMVPUniformAllObjects()
{
	setupModelViewProjectionTransform();
	// For every object, setup VAO's / buffers
	for(unsigned int i = 0; i < toRender.size(); i++)
	{
		Renderable & current = *toRender.at(i);
		RenderingTools::reloadMVPUniform(current);
	}
	glutPostRedisplay();
}

void displayFunc()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	// Render all objects!
	//TODO: move this into renderable as an overridable
	//		function so each child can render differently
	//		(eg. pass in additional buffers)
	for(unsigned int i = 0; i < toRender.size(); i++)
	{
		Renderable & current = *toRender.at(i);
		RenderingTools::loadBuffer(current);

		// Use our shader
		glUseProgram( current.basicProgramID );

		// Use VAO that holds buffer bindings
		// and attribute config of buffers
		glBindVertexArray( current.vaoID );

		if(current.useIndexBuffer)
		{

			glDrawElements(GL_TRIANGLES,               // mode
			                 current.getIndices().size(), // count
			                 GL_UNSIGNED_INT,            // type
			                 (void *)0                   // element array buffer offset
			                 );
		}
		else
		{
			glDrawArrays( current.getRenderMode(), 0, current.getVerts().size() );
		}

	}

	glutSwapBuffers();
}


void idleFunc()
{
	particleSystem.update();

	//M = M * RotateAboutYMatrix(1);
	setupModelViewProjectionTransform();
    reloadMVPUniformAllObjects();

	glutPostRedisplay();
}

void resizeFunc( int width, int height )
{
    WIN_WIDTH = width;
    WIN_HEIGHT = height;

    glViewport( 0, 0, width, height );

    loadProjectionMatrix();
    reloadMVPUniformAllObjects();

    glutPostRedisplay();
}


void loadProjectionMatrix()
{
    // Perspective Only

	// field of view angle 60 degrees
	// window aspect ratio
	// near Z plane > 0
	// far Z plane

    P = PerspectiveProjection(  60, // FOV
                                static_cast<float>(WIN_WIDTH)/WIN_HEIGHT, // Aspect
                                0.01,   // near plane
                                50 ); // far plane depth
}

void loadModelViewMatrix()
{
    M = UniformScaleMatrix( 0.5 );	// scale Scene First

    M = TranslateMatrix( 0, 0, -3 ) * M;	// translate away from (0,0,0)

    // view doesn't change, but if it did you would use this
    V = IdentityMatrix();
}

void setupModelViewProjectionTransform()
{
	for(unsigned int i = 0; i < toRender.size(); i++)
	{
		Renderable & current = *toRender.at(i);

		current.MVP = P * V * M * current.M;
	}
}

float RandomWithinBounds(float lowerBound, float upperBound)
{
	float frand = (float)std::rand()/(float)RAND_MAX;
	float upperLower = upperBound - lowerBound;

	return frand * upperLower + lowerBound;
}

void init()
{
	glEnable( GL_DEPTH_TEST );
	std::srand(time(0));

	std::vector<Particle*> particles;
	// Create particles

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			for(int k = 0; k < 2; k++)
			{
				BoidParticle * newParticle = new BoidParticle(Vec3f(
						RandomWithinBounds(-WIDTH/2, WIDTH/2),
						RandomWithinBounds(-HEIGHT/2, HEIGHT/2),
						RandomWithinBounds(-DEPTH/2, DEPTH/2)));
				particles.push_back(newParticle);
			}
		}

	}

	particleSystem.setParticles(particles);
	particleSystem.fillVoxels();

	setupBounds();


	// SETUP SHADERS, BUFFERS, VAOs

    loadModelViewMatrix();
    loadProjectionMatrix();
	setupModelViewProjectionTransform();

	// For every object, setup VAO's / buffers
	for(unsigned int i = 0; i < toRender.size(); i++)
	{
		Renderable & current = *toRender.at(i);
		current.generateIDs();
		RenderingTools::setupVAO(current);
		RenderingTools::loadBuffer(current);
		if(current.useIndexBuffer)
			RenderingTools::loadIndexBuffer(current);
		RenderingTools::reloadMVPUniform(current);
	}


}

void menu(int choice)
{

}


int main( int argc, char** argv )
{
	glutInit( &argc, argv );
	// Setup FB configuration
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	
	glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );
	glutInitWindowPosition( 0, 0 );

	glutCreateWindow( "Particle Simulator" );

	glewExperimental=true; // Needed in Core Profile
	// Comment out if you want to us glBeign etc...
	if( glewInit() != GLEW_OK )
	{
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	cout << "GL Version: :" << glGetString(GL_VERSION) << endl;

    glutDisplayFunc( displayFunc );
	glutReshapeFunc( resizeFunc );
    glutIdleFunc( idleFunc );
    glutMouseFunc( mouseButtonFunc );
    glutMotionFunc( mouseMotionFunc);

    glutCreateMenu(menu);
    glutAddMenuEntry("MENU OPTIONS!",0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	init(); // our own initialize stuff func

	glutMainLoop();

	// clean up after loop
	for(unsigned int i = 0; i < toRender.size(); i++)
	{
		Renderable & current = *toRender.at(i);

		current.deleteIDs();
	}

	particleSystem.freePointers();

	return 0;
}
