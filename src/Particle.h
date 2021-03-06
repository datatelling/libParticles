#ifndef PARTICLE
#define PARTICLE

#include "ofMain.h"

struct pPoint{
    ofPoint pos;
    ofFloatColor color;
};

class Particle : public ofPoint {
public:
    
    Particle();
    
    void    init(ofPoint _pos, ofPoint _vel);
    
    ofPoint getVel(){return vel;};
    
    void    addForce( ofPoint _force );
    void    addNoise(float _angle, float _turbulence);
    
    void    addRepulsionForce(ofPoint p, float radius, float scale);
    void    addAttractionForce(ofPoint p, float radius, float scale);
    void    addRepulsionForce(Particle *p, float radius, float scale);
    void    addAttractionForce(Particle *p, float radius, float scale);
    void    addClockwiseForce(Particle *p, float radius, float scale);
    void    addCounterClockwiseForce(Particle *p, float radius, float scale);
    
    ofFloatColor color;
    
    ofPoint      origin;
    ofPoint      destiny;
    
    void    update();
    void    draw();
    
    float   damping;
    float   size;
    
private:
    ofPoint vel;
    ofPoint acc;
};

#endif
