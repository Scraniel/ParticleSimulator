#ifndef OPENGL_MAT_TOOLS_H
#define OPENGL_MAT_TOOLS_H

#define _USE_MATH_DEFINES
#include <cmath>

#include "../MathTools/Mat4f.h"

Mat4f IdentityMatrix();
Mat4f UniformScaleMatrix( float scale );
Mat4f ScaleMatrix( float x, float y, float z );
Mat4f TranslateMatrix( float x, float y, float z );
Mat4f RotateAboutXMatrix( float angleDeg );
Mat4f RotateAboutYMatrix( float angleDeg );
Mat4f RotateAboutZMatrix( float angleDeg );

Mat4f OrthoProjection( 	float left, float right,
			float top, float bottom,
			float far, float near );

Mat4f PerspectiveProjection( 	float fov, float aspectRatio,
				float zNear, float zFar );

#endif // OPENGL_MAT_TOOLS_H
