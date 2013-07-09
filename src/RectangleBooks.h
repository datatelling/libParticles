//
//  RectangleBooks.h
//  cLibrary
//
//  This is a class that extends from ofRectangle to deal with
//  the boxes and books (points).
//

#pragma once

#include "ofMain.h"

class RectangleBooks: public ofRectangle{
public:
    
    void    getPoints( vector<ofPoint> &_pnts );
    void    draw();
    
    string  text;
    float   color;    // just brightness
};
