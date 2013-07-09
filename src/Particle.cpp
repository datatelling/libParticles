#include "Particle.h"

//------------------------------------------------------------
Particle::Particle(){
	this->set(0.0,0.0,0.0);
    vel.set(ofRandom(-10,10), ofRandom(-10,10));
    acc.set(0,0,0);
    
    size = 1.0;
	damping = 0.07f;
}

void Particle::init(ofPoint _pos, ofPoint _vel){
    this->set(_pos);
    origin.set(_pos);
    vel.set(_vel);
}

//------------------------------------------------------------
void Particle::addForce(ofPoint _force){
    acc += _force;
}

//------------------------------------------------------------
void Particle::addNoise(float _angle, float _turbulence){
    
    float angle = ofSignedNoise( x * 0.005f, y * 0.005f) * _angle;
    
    ofPoint noiseVector( cos( angle ), sin( angle ) );
    
    acc += noiseVector * _turbulence;
}

//------------------------------------------------------------
void Particle::update(){
	
    vel += acc;
    vel *= 1.0f - damping;
    *this += vel;

    acc *= 0;
}

void Particle::draw(){
    ofPushStyle();
    ofSetColor(color);
    ofRect(*this,size,size);
    ofPopStyle();
}

//------------------------------------------------------------
void Particle::addRepulsionForce(ofPoint posOfForce, float radius, float scale){
    
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= *this - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
        acc += diff * scale * pct;
    }
}

//------------------------------------------------------------
void Particle::addAttractionForce(ofPoint posOfForce, float radius, float scale){
	
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= (*this) - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		acc -= diff * scale * pct;
    }
}

//------------------------------------------------------------
void Particle::addRepulsionForce(Particle *p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Particle p is:
	ofPoint posOfForce;
	posOfForce.set(*p);
	
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= (*this) - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		addForce(diff * scale * pct);
        p->addForce(diff * scale * pct * -1);
    }
}

//------------------------------------------------------------
void Particle::addAttractionForce(Particle *p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Particle p is:
	ofPoint posOfForce;
	posOfForce.set(*p);
	
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= (*this) - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
        addForce(diff * scale * pct * -1);
        p->addForce(diff * scale * pct);
    }
	
}

//------------------------------------------------------------
void Particle::addClockwiseForce(Particle *p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Particle p is:
	ofPoint posOfForce;
	posOfForce.set(*p);
	
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= (*this) - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
        addForce(ofPoint(diff.y * scale * pct * -1,
                         diff.x * scale * pct));
        p->addForce(ofPoint(diff.y * scale * pct,
                           diff.x * scale * pct * -1));
    }
}

//------------------------------------------------------------
void Particle::addCounterClockwiseForce(Particle *p, float radius, float scale){
	
	// ----------- (1) make a vector of where this Particle p is:
	ofPoint posOfForce;
	posOfForce.set(*p);
	
	// ----------- (2) calculate the difference & length
	
	ofPoint diff	= (*this) - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
        addForce(ofPoint(diff.y * scale * pct,
                         diff.x * scale * pct * -1));
        p->addForce(ofPoint(diff.y * scale * pct * -1,
                           diff.x * scale * pct));
    }
}