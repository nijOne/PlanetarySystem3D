#include "include/SolarSystem.hpp"

#include <GL/glu.h>
#include <sstream>


// Planetary system simulation //  g++ main.cpp -o output `pkg-config --cflags --libs opencv`   
/* todo                                                  // ideas & questions

    Set scene                                          encapsulation - do i need it? 
    posZ !!
	refractoring                                         
	destructors                                         
    Apply OpenGL knowledge
	...                                                                    
*/

const int FRAME_HEIGHT = 800;
const int FRAME_WIDTH = 800;

void drawScene() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

    solarSystem->initializeBodies();
   
    glFlush();
    glutSwapBuffers();
}


void reshape(int w, int h) {

    if(w == 0) w = 1;
    if(h == 0) h = 1;

    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(w < h) 
        glOrtho(-1.0f, 1.0f, -1.0f * h / w, 1.0f * h / w, 1.0f, -1.0f);
    else 
        glOrtho(-1.0f * w / h, 1.0f * w / h, -1.0f, 1.0f, 1.0f, -1.0f);

    drawScene();
}

int main(int argc, char** argv) {

    solarSystem = new PlanetarySystem("Solar System");
    
    initSolarSystem();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(FRAME_WIDTH, FRAME_HEIGHT);
    glutCreateWindow("Planetary System 3D");

    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}