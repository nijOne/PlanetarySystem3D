#ifndef SolarSystem_HPP
#define SolarSystem_HPP

#include "PlanetarySystem.hpp"

PlanetarySystem* solarSystem = nullptr;

nColor sunColor(255,204,51);

nColor whiteColor(255,255,255);

nColor mercuryColor(169,169,169);
nColor venusColor(255,255,153);
nColor earthColor(51,153,255);
nColor marsColor(193,68,14);
nColor jupiterColor(253,166,0);
nColor saturnColor(238,232,170);
nColor uranusColor(176,216,230);
nColor neptuneColor(135,206,250);

void initSolarSystem() {

    solarSystem->setSource("Sun", 1.0, 109, &sunColor);
        //addPlanet(name, massInEarthMass, radiusInEarthRadius, semiMajorAxis, eccentricy, omega, color)
    solarSystem->addPlanet("Mercury", 0.05528, 0.38709, 0.3829, 0.20563, 48.33, &mercuryColor);
    solarSystem->addPlanet("Venus", 0.81500, 0.72333, 0.9499, 0.00677, 76.68, &venusColor);
    solarSystem->addPlanet("Earth", 1.0, 1.0, 1.0, 0.01671, 0, &earthColor);
    solarSystem->addPlanet("Mars", 0.10745, 0.533, 1.52366, 0.09341, 49.58, &marsColor);
    solarSystem->addPlanet("Jupiter", 317.83, 5.20366, 10.973, 0.04839, 100.56, &jupiterColor);
    solarSystem->addPlanet("Saturn", 95.159, 9.53707, 9.449, 0.05415, 113.72, &saturnColor);
    solarSystem->addPlanet("Uranus", 14.536, 19.19126, 4.007, 0.04717, 74.23, &uranusColor);
    solarSystem->addPlanet("Neptune", 17.147, 30.06896, 3.883, 0.00859, 131.72, &neptuneColor);
        //addSatelliteToPlanet(satelliteName, planetName, massInEarthMass, radiusInEarthRadius, semiMajorAxis, eccentricy, omega, color)
    solarSystem->addSatelliteToPlanet("Moon", "Earth", 0.0123, 0.273, 0.00257, 0.0, 0, &whiteColor);
    solarSystem->addSatelliteToPlanet("Phobos", "Mars", 1.78477e-9, 1.76941e-3, 9376e3 / CelestialBody::ASTRONOMICALUnit, 0.0151, 20, &whiteColor);
    solarSystem->addSatelliteToPlanet("Deimos", "Mars", 0.247179e-9, 0.97316e-3, 23463.2e3 / CelestialBody::ASTRONOMICALUnit, 0.00033, 89, &whiteColor);
}


#endif