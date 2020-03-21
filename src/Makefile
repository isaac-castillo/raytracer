CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -g -O3 -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -O3 -g -fopenmp -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib  \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif

RM = /bin/rm -f 
all: raytracer
raytracer: main.o Transformer.o Camera.o FileReader.o Scene.o RayTracer.o Shape.o Light.o Light.h Shape.h Transformer.h Camera.h FileReader.h Scene.h RayTracer.h 
	$(CC) $(CFLAGS) -o raytracer main.o Transformer.o Light.o FileReader.o Scene.o Camera.o RayTracer.o Shape.o $(INCFLAGS) $(LDFLAGS) 
tester: Tests.o Transformer.o Camera.o FileReader.o Scene.o RayTracer.o Shape.o Shape.h Transformer.h Camera.h FileReader.h Scene.h RayTracer.h 
	$(CC) $(CFLAGS) -o raytracer Tests.o Transformer.o FileReader.o Scene.o Camera.o RayTracer.o Shape.o $(INCFLAGS) $(LDFLAGS) 
Tests.o: Tests.cpp
		$(CC) $(CFLAGS) $(INCFLAGS) -c Tests.cpp

main.o: main.cpp  
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
RayTracer.o: RayTracer.cpp RayTracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c RayTracer.cpp
Light.o: Light.cpp Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Light.cpp
Shape.o: Shape.cpp Shape.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Shape.cpp
Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Scene.cpp
Camera.o: Camera.cpp Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp
FileReader.o: FileReader.cpp FileReader.h  
	$(CC) $(CFLAGS) $(INCFLAGS) -c FileReader.cpp
Transformer.o: Transformer.cpp Transformer.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transformer.cpp  
#Geometry.o: Geometry.cpp Geometry.h Transform.h variables.h
#	$(CC) $(CFLAGS) $(INCFLAGS) -c Geometry.cpp
clean: 
	$(RM) *.o raytracer *.png