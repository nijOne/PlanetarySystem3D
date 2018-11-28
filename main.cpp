#include "include/PlanetarySystem.hpp"
#include <sstream>

// Planetary system simulation //  g++ main.cpp -o output `pkg-config --cflags --libs opencv`   
/* todo                                                  // ideas & questions

    Camera movement                                         encapsulation - do i need it? 
    posZ !!
	refractoring                                         
	destructors                                         
    Apply OpenGL knowledge
	...                                                                    
*/

const int FRAME_HEIGHT = 800;
const int FRAME_WIDTH = 800;

PlanetarySystem* solarSystem = NULL;

nColor sunColor(255,204,51);
nColor moonColor(255,255,255);
nColor mercuryColor(169,169,169);
nColor venusColor(255,255,153);
nColor earthColor(51,153,255);
nColor marsColor(193,68,14);
nColor jupiterColor(253,166,0);
nColor saturnColor(238,232,170);
nColor uranusColor(176,216,230);
nColor neptuneColor(135,206,250);

void drawScene() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
  
    solarSystem->initializeBodies();
   
    glFlush();
    glutSwapBuffers();
}


void reShape(int w, int h) {

    if(w == 0) w = 1;
    if(h == 0) h = 1;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);

    if(w < h) 
        glOrtho(-1.0f, 1.0f, -1.0f * h / w, 1.0f * h / w, 1.0f, -1.0f);
    else 
        glOrtho(-1.0f * w / h, 1.0f * w / h, -1.0f, 1.0f, 1.0f, -1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {

    int hoursPerFrame = 1;
    int FPS = 24;

    GLdouble AU = CelestialBody::ASTRONOMICALUnit;

    solarSystem = new PlanetarySystem("Solar System");
    
    solarSystem->setSource("Sun", 1.0, 109, &sunColor);

    solarSystem->addPlanet("Mercury", 0.05528, 0.38709, 0.3829, 0.20563, 48.33, &mercuryColor);
    solarSystem->addPlanet("Venus", 0.81500, 0.72333, 0.9499, 0.00677, 76.68, &venusColor);
    solarSystem->addPlanet("Earth", 1.0, 1.0, 1.0, 0.01671, 0, &earthColor);
    solarSystem->addPlanet("Mars", 0.10745, 0.533, 1.52366, 0.09341, 49.58, &marsColor);
    solarSystem->addPlanet("Jupiter", 317.83, 5.20366, 10.973, 0.04839, 100.56, &jupiterColor);
    solarSystem->addPlanet("Saturn", 95.159, 9.53707, 9.449, 0.05415, 113.72, &saturnColor);
    solarSystem->addPlanet("Uranus", 14.536, 19.19126, 4.007, 0.04717, 74.23, &uranusColor);
    solarSystem->addPlanet("Neptune", 17.147, 30.06896, 3.883, 0.00859, 131.72, &neptuneColor);

    solarSystem->addSatelliteToPlanet("Moon", "Earth", 0.0123, 0.273, 0.00257, 0.0, 0, &moonColor);
    solarSystem->addSatelliteToPlanet("Phobos", "Mars", 1.76941e-3, 9376e3/AU, 0.0151, 1.78477e-9, 20, &moonColor);
    solarSystem->addSatelliteToPlanet("Deimos", "Mars", 0.97316e-3, 23463.2e3/AU, 0.00033, 0.247179e-9, 89, &moonColor);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(FRAME_WIDTH, FRAME_HEIGHT);
    glutCreateWindow("Planetary System 3D");

    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);

    glutReshapeFunc(reShape);
    //createMenus();
    //createGLUTMenus();


  //  glutEntryFunc(mouseLeft);
  //  glutKeyboardFunc(kbEvent);
  //  glutSpecialFunc(kbEventSpecial);
  //  glutMouseFunc(mouseButton);
  //  glutMotionFunc(mouseButtonAndMove);
  //  glutPassiveMotionFunc(mouseMove);
  //  glutMotionFunc(mouseButtonAndMove);

    glutMainLoop();
}