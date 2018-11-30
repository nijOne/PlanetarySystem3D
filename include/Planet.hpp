#ifndef Planet_HPP
#define Planet_HPP

#include "Satellite.hpp"
#include "CelestialBody.hpp"

class Planet : public CelestialBody {
    public:

    vector<Satellite*> satellitesPTR;
    map<string, Satellite*> satelliteMAP;

    Planet(string name, GLdouble massInEarthMass, GLdouble radiusInEarthRadius) {

        this->name = name;
        this->mass = massInEarthMass * CelestialBody::MASSOfEarth;
        this->radius = 1000 * radiusInEarthRadius * RADIUSOfEarth / ASTRONOMICALUnit;
    }

    void addSatellite(string name, GLdouble massInEarthMass, GLdouble radiusInEarthRadius, GLdouble semiMajorAxis, GLdouble eccentricy, GLdouble omega, nColor* color) {
        
        satellitesPTR.push_back(new Satellite(name, mass, radiusInEarthRadius));

        satellitesPTR.back()->setEllipseParameters(semiMajorAxis, eccentricy, omega);
        satellitesPTR.back()->setSource(this);
        satellitesPTR.back()->setColor(color);

        satellitesPTR.back()->calcPeriod();

        satelliteMAP[name] = satellitesPTR.back();
    }

    void setBodyOnScene() {

        glPushMatrix();
        glTranslatef(position3d.posX, position3d.posY, position3d.posZ);
        getColor();
        glutWireSphere(radius, 10, 10);
        glPopMatrix();
    }
};

#endif
