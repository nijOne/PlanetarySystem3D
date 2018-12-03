#ifndef CelestialBody_HPP
#define CelestialBody_HPP

#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <map>

#include <GL/glut.h>

using namespace std;

struct nCoords {

    GLdouble posX = 0.0;
    GLdouble posY = 0.0;
    GLdouble posZ = 0.0;

    nCoords() {

    }

    nCoords(GLdouble posX, GLdouble posY, GLdouble posZ) {

        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;
    }
};

struct nColor {

    GLdouble red = 0.0;
    GLdouble green = 0.0;
    GLdouble blue = 0.0;

    nColor() {

    }

    nColor(GLdouble red, GLdouble green, GLdouble blue) {

        this->red = red / 255;
        this->green = green / 255;
        this->blue = blue / 255;
    }
};

class CelestialBody {

    public:

    string name = "";

    CelestialBody *source = nullptr;

    nCoords position3d;
    nColor *color = nullptr;

    GLdouble mass = 0;                                            // [kg]
    GLdouble radius = 0;                                          // [m]

    GLdouble distanceFromSource = 0;                              // [m]
    GLdouble semiMajorAxis = 0;                                   // [m]
    GLdouble eccentricy = 0;                                      // 

    GLdouble dt = 86400;	                                      // [s] // jeden dzien w sekundach
    GLdouble omega = 0;                                           // [stopnie]

    GLdouble ORBITPeriodCONST =  0;                               //
    GLdouble periodT = 0;    

    constexpr static GLdouble RADIUSOfEarth = 6.37814e6;          // [m] 
    constexpr static GLdouble MASSOfEarth = 5.97219e24;           // [kg]
    constexpr static GLdouble GRAVConst = 6.67408e-11;            // [m^3/(kg*s^2)];
    constexpr static GLdouble MASSOfSun = 1.98855e30;             // [kg]
    constexpr static GLdouble ASTRONOMICALUnit = 1.49598e11;      // [m]

    CelestialBody() {

        cout << "Default CelesitialBody Contructor Called" << endl;
    }

    CelestialBody(string name, GLdouble massInEarthMass, GLdouble radiusInEarthRadius) {
        
        cout << "CelestialBody constructor called " << name << endl;
        this->name = name;
        this->mass = massInEarthMass * CelestialBody::MASSOfEarth;
        this->radius = radiusInEarthRadius * RADIUSOfEarth / ASTRONOMICALUnit;
    }

    ~CelestialBody() {
        
        cout << "Destructor called" << name << endl;
    }

    virtual void setBodyOnScene() = 0;

    void setColor(nColor* color) {

        this->color = color ;
    }

    void getColor() {

        glColor3d(color->red, color->green, color->blue);
    }

    void calcDistanceAndPosition(GLfloat dayCount) {

        GLdouble theta = dayCount * calcThetaFromTimeGap();
        distanceFromSource = semiMajorAxis * (1 - pow(eccentricy,2)) / ( 1 + eccentricy * cos(theta*M_PI/180));

        position3d.posX = source->position3d.posX + distanceFromSource * cos((omega + theta)*M_PI/180) / ASTRONOMICALUnit;
        position3d.posY = source->position3d.posY + distanceFromSource * sin((omega + theta)*M_PI/180) / ASTRONOMICALUnit;
        position3d.posZ = source->position3d.posZ + 0.0;
    }

    void calcPeriod() {

        ORBITPeriodCONST = 4.0*M_PI*M_PI/(GRAVConst * source->mass );
        periodT = sqrt(pow(semiMajorAxis,3)*ORBITPeriodCONST);
    }

    GLdouble calcThetaFromTimeGap() {

        return dt * 360 / periodT;
    }

    void setEllipseParameters(GLdouble semiMajorAxis, GLdouble eccentricy, GLdouble omega) {

        this->semiMajorAxis = semiMajorAxis * ASTRONOMICALUnit;
        this->eccentricy = eccentricy;
        this->omega = omega;
    }

    void setSource(CelestialBody* source) {
        
        this->source = source;
    }

    void getPosition() {
        
        cout << position3d.posX << " " << position3d.posY << " " << position3d.posZ << endl;
        cout << radius << endl;
    }

    virtual void getPositionVector() {

        getColor();
        glVertex3d(source->position3d.posX, source->position3d.posY, source->position3d.posZ);
        glVertex3d(position3d.posX, position3d.posY, position3d.posZ);
    }

    void getInfo() {

        cout << "Name: " << name << endl;
        cout << "Mass: " << mass << endl;
        cout << "Radius: " << radius << endl;
        cout << "Distance: " << distanceFromSource << endl;
        cout << "Position: " << endl;
        cout << "   X = " << position3d.posX << endl;
        cout << "   Y = " << position3d.posY << endl;
        cout << "   Z = " << position3d.posZ << endl;

    }
};

#endif