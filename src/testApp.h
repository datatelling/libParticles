#pragma once

#include "ofMain.h"

#include "Particle.h"
#include "RectangleBooks.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void makeScene();
    
    //  4 sections of the big box of the library
    //
    RectangleBooks          archiveBooks[4];
    
    vector<Particle>        publicBooks;
    vector<RectangleBooks>  categories;
    
    float   totalWidth, totalHeight;
    float   publicBooksColor;
    
    //  Camera transitions
    //
    ofPoint translate;
    float   scale;
    bool    bZoomOut;
};
