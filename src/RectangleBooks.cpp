//
//  RectangleBooks.cpp
//  cLibrary
//
//

#include "RectangleBooks.h"

void RectangleBooks::getPoints(vector<ofPoint> &_pnts){
    for (int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++){
            _pnts.push_back(ofPoint(x+i,y+j));
        }
    }
}

void RectangleBooks::draw(){
    ofPushStyle();
    ofSetColor(ofFloatColor(color));
    ofRect(*this);
    
    ofSetColor(255,(1.0-color)*255*10.0);
    ofDrawBitmapString(text, x+15, y+35);
    ofPopStyle();
}