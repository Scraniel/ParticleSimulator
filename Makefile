CC=g++

CFLAGS=-c -std=c++11 -O0 -Wall -g
LDFLAGS=-lGLEW -lGL -lglut -lXi -lpthread -L/usr/lib64
SOURCES=main.cpp OpenGLTools/ShaderTools.cpp OpenGLTools/RenderingTools.cpp MathTools/Mat4f.cpp MathTools/OpenGLMatrixTools.cpp MathTools/Vec3f.cpp MathTools/VectorTools.cpp SceneObjects/Renderable.cpp SceneObjects/ParticleSystem.cpp SceneObjects/Particles/Particle.cpp SceneObjects/Particles/SPHParticle.cpp SceneObjects/Particles/BoidParticle.cpp Helpers/FileHelper.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BIN=bin/
OBJ=$(BIN)obj/
EXECUTABLE=$(BIN)ParticleSimulator

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	mv */Particles/*.o $(OBJ)
	mv */*.o $(OBJ)
	mv *.o $(OBJ) 
	

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)*.o *.o */*.o */*/*.o $(EXECUTABLE)
