#ifndef Star_HPP
#define Star_HPP

#include "CelestialBody.hpp"

class Star : public CelestialBody {
    public:

    Star(string name, GLdouble massInSunMass, GLdouble radiusInEarthRadius) {

        this->name = name;
        this->mass = massInSunMass*MASSOfSun;
        this->radius = radiusInEarthRadius * RADIUSOfEarth / ASTRONOMICALUnit;
    }

    void setBodyOnScene() {

        glPushMatrix();
        glTranslated(position3d.posX, position3d.posY, position3d.posZ);
        getColor();
        glutWireSphere(radius, 10, 10);
        glPopMatrix();
    }  

    void getPositionVector() {

        getColor();
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(position3d.posX, position3d.posY, position3d.posZ);
    }
};

#endif