#ifndef PlanetarySystem_HPP
#define PlanetarySystem_HPP

#include "CelestialBody.hpp"
#include "Star.hpp"
#include "Planet.hpp"
#include "Satellite.hpp"

#include <chrono>
#include <thread>

class PlanetarySystem {
    public:

    string name = "";
    CelestialBody* sourceStar = nullptr;
    vector<Planet*> planetsPTR;
    map<string, Planet*> planetsMAP;

    GLfloat dayCount = 0.0;

    PlanetarySystem(string name) {

        cout << "PlanetarySystem constructor called" << endl;
        this->name = name;
    }

    ~PlanetarySystem() {

         for (vector<Planet*>::iterator itP = planetsPTR.begin(); itP != planetsPTR.end(); itP++) { 
            if( !(*itP)->satellitesPTR.empty()) {

                for( vector<Satellite*>::iterator itS = (*itP)->satellitesPTR.begin(); itS != (*itP)->satellitesPTR.end(); itS++) 
                    delete (*itS);                    

                delete (*itP);
            } else {
                
                delete (*itP);
            }
        }

        delete sourceStar;

        cout << "Planetary System destructor called" << endl;
    }

    void setSource(string name, GLdouble mass, GLdouble radius, nColor* color) {

        sourceStar = new Star(name, mass, radius);
        sourceStar->setColor(color);
    }

    void addPlanet(string name, GLdouble massInEarthMass, GLdouble radiusInEarthRadius, GLdouble semiMajorAxis, GLdouble eccentricy, GLdouble omega, nColor* color) {
    
        planetsPTR.push_back(new Planet(name, massInEarthMass, radiusInEarthRadius));
        
        planetsPTR.back()->setSource(sourceStar);
        planetsPTR.back()->setEllipseParameters(semiMajorAxis, eccentricy, omega);
        planetsPTR.back()->setColor(color);

        planetsPTR.back()->calcPeriod();

        planetsMAP[name] = planetsPTR.back();
    }

    void addSatelliteToPlanet(string satelliteName, string planetName, GLdouble massInEarthMass, GLdouble radiusInEarthRadius, GLdouble semiMajorAxis, GLdouble eccentricy, GLdouble omega, nColor* color) {

        planetsMAP[planetName]->addSatellite(satelliteName, massInEarthMass, radiusInEarthRadius, semiMajorAxis, eccentricy, omega, color);
    }

    void initializeBodies() {

        sourceStar->setBodyOnScene();
        
        for (vector<Planet*>::iterator itP = planetsPTR.begin(); itP != planetsPTR.end(); itP++) {

            (*itP)->calcDistanceAndPosition(dayCount);
            (*itP)->setBodyOnScene();
            
            if( !(*itP)->satellitesPTR.empty()) {
                for( vector<Satellite*>::iterator itS = (*itP)->satellitesPTR.begin(); itS != (*itP)->satellitesPTR.end(); itS++) {

                    (*itS)->calcDistanceAndPosition(dayCount);                   
                    (*itS)->setBodyOnScene();
                }
            }

            this_thread::sleep_for(chrono::milliseconds(10));
            dayCount += 1.0 / 24;
        }

        glEnd();
    }

    void initializeVectors() {

        sourceStar->getPositionVector();
        
        for (vector<Planet*>::iterator itP = planetsPTR.begin(); itP != planetsPTR.end(); itP++) {

            (*itP)->calcDistanceAndPosition(dayCount);
            (*itP)->getPositionVector();
            
            if( !(*itP)->satellitesPTR.empty()) {
                for( vector<Satellite*>::iterator itS = (*itP)->satellitesPTR.begin(); itS != (*itP)->satellitesPTR.end(); itS++) {

                    (*itS)->calcDistanceAndPosition(dayCount);                   
                    (*itS)->getPositionVector();
                }
            }

            this_thread::sleep_for(chrono::milliseconds(10));
            dayCount += 1.0 / 24;
        }

        glEnd();
    }

    void daysPerFrame(float n) {

        dayCount += n;
    }

};
#endif