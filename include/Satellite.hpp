#ifndef Satellite_HPP
#define Satellite_HPP

#include "CelestialBody.hpp"


class Satellite : public CelestialBody {
    public:

    Satellite(string name, GLdouble massInEarthMass, GLdouble radiusInEarthRadius) {

        this->name = name;
        this->mass = massInEarthMass * CelestialBody::MASSOfEarth;
        this->radius = 100 * radiusInEarthRadius * RADIUSOfEarth / ASTRONOMICALUnit;
    }

    void setBodyOnScene() {

        glPushMatrix();
        glTranslated(source->position3d.posX, source->position3d.posY, source->position3d.posZ);
        glTranslatef(position3d.posX, position3d.posY, position3d.posZ);
        getColor();
        glutWireSphere(radius, 10, 10);
        glPopMatrix();
    }
};

#endif