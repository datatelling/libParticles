#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofEnableSmoothing();

    //  Total dimensions of the Cubelibrary
    //
    totalWith = 1000;
    totalHeight = 1000;
    
    //  Prepare everything for the show
    //
    makeScene();
}

void testApp::makeScene(){
    
    //  initial Camera Zoom and Pan position
    //
    scale = 0.1;
    translate.set(0,0);
    
    //  Place the books rectangles that represent the 4 sections of all the data
    //
    archiveBooks[0].x = 0;
    archiveBooks[0].y = totalHeight*0.8934;
    archiveBooks[0].width = totalWith;
    archiveBooks[0].height = totalHeight*0.1066;
    archiveBooks[0].color = 1.0;
    archiveBooks[0].text = "A";
    
    archiveBooks[1].x = 0;
    archiveBooks[1].y = 0;
    archiveBooks[1].width = totalWith;
    archiveBooks[1].height = totalHeight*0.8934;
    archiveBooks[1].color = 1.0;
    archiveBooks[1].text = "B";
    
    archiveBooks[2].x = archiveBooks[1].getLeft()+totalWith*0.548;
    archiveBooks[2].y = archiveBooks[1].getTop()+totalHeight*0.6434;
    archiveBooks[2].width = totalWith*0.452;
    archiveBooks[2].height = totalHeight*0.25;
    archiveBooks[2].color = 1.0;
    archiveBooks[2].text = "C";
    
    //  Public books
    //
    archiveBooks[3].x = archiveBooks[1].getLeft()+totalWith*0.849;
    archiveBooks[3].y = archiveBooks[1].getTop()+totalHeight*0.7734;
    archiveBooks[3].width = totalWith*0.151;
    archiveBooks[3].height = totalHeight*0.12;
    archiveBooks[3].color = 0.0;                    // we don't want to draw this section of the library.
                                                    // Actually just to draw a black box
    archiveBooks[3].text = "D";
    
    publicBooksColor = 1.0;     // Color of the particles
    
    
    //  Set the categories
    //
    categories.clear();
    RectangleBooks cat;
    cat.text = "Cat 01";
    cat.x = archiveBooks[3].getTopRight().x + 50;
    cat.y = archiveBooks[3].getTopRight().y - 100;
    cat.width = 20;
    cat.height = 100;
    cat.color = 0.0;
    categories.push_back(cat);
    
    cat.text = "Cat 02";
    cat.x += 40;
    cat.width = 80;
    
    categories.push_back(cat);
    
    cat.text = "Cat 03";
    cat.x += 100;
    cat.width = 50;
    categories.push_back(cat);
    
    cat.text = "Cat 04";
    cat.x += 70;
    cat.width = 10;
    categories.push_back(cat);
    
    // Place the particles
    //
    float width = 435;
    float height = 345;
    float scaleWidth = archiveBooks[3].width/width;
    float scaleHeight = archiveBooks[3].height/height;
    
    publicBooks.clear();
    for (int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++){
            Particle p;
            p.init(ofPoint(archiveBooks[3].x + (float)(x)*scaleWidth ,
                           archiveBooks[3].y + (float)(y)*scaleHeight ),
                   ofPoint(0,0));
            p.color = 0.7;
            publicBooks.push_back(p);
        }
    }
    
    //  Assign categories (places inside it) to particles
    //  there are smarter and better ways to do this
    //
    int cIndex = 0;
    int lastTotal = 0;
    for(int i = 0; i < publicBooks.size(); i++){

        vector<ofPoint> positions;
        categories[cIndex].getPoints(positions);
        
        publicBooks[i].destiny = positions[(i-lastTotal)%positions.size()];
        
        if( (i-lastTotal) == positions.size()-2){
            lastTotal += positions.size()-1;
            cIndex++;
            if (cIndex >= categories.size()){
                break;
            }
        }
    }
    
    //  - OR - 
    
//    vector<ofPoint> totalCategoryPostions;
//    
//    //  Add all the positions on the categories
//    //
//    for (int i = 0; i < categories.size(); i++) {
//        categories[i].getPoints(totalCategoryPostions);
//    }
//    
//    //  go for all that positions and asigned them to random particles
//    //
//    for (int i = 0; i < totalCategoryPostions.size(); i++){
//        publicBooks[ ofRandom(publicBooks.size()) ].destiny = totalCategoryPostions[i];
//    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    //  Camera move
    //  ---------------------------------
    //  All is hook to the scale... witch will work as a timeline
    //  Things will happend at specific moments of time dictated by
    //  scale value
    //
    if (bZoomOut && scale > 0.1){
        scale -= 0.01;
    } else if (scale < 1.0 && !bZoomOut){
        //scale += 0.001;
        scale += 0.005;
    } else if ( scale < 3.0 && !bZoomOut){
        //scale += 0.0001;
        scale += 0.0005;
    }

    if (scale > 0.8 && !bZoomOut){
        ofPoint center = ofPoint(totalWith*0.5,totalHeight*0.5);
        ofPoint diff = center - archiveBooks[3].getCenter();
        diff.x -= totalWith*0.5;
        translate.x = ofLerp(translate.x, diff.x, 0.01);   // Lerp is use to interpolate values gradualy
        translate.y = ofLerp(translate.y, diff.y, 0.01);   //
        
        publicBooksColor = ofLerp(publicBooksColor, 0.7, 0.001);    // We have it to do it also with the particles
    }
    
    //  Colors ( also depend on the scale )
    //
    if (scale > 0.1 && !bZoomOut){
        //archiveBooks[1].color = ofLerp( archiveBooks[1].color, 0.9, 0.001);
        //archiveBooks[2].color = ofLerp( archiveBooks[2].color, 0.9, 0.001);
        //publicBooksColor = ofLerp(publicBooksColor, 0.9, 0.001);
        archiveBooks[1].color = ofLerp( archiveBooks[1].color, 0.8, 0.005);
        archiveBooks[2].color = ofLerp( archiveBooks[2].color, 0.8, 0.005);
        publicBooksColor = ofLerp(publicBooksColor, 0.8, 0.005);
    }
    
    if (scale > 0.5 && !bZoomOut){
        //archiveBooks[2].color = ofLerp(archiveBooks[2].color, 0.8, 0.001);
        //publicBooksColor = ofLerp(publicBooksColor, 0.8, 0.001);
        archiveBooks[2].color = ofLerp(archiveBooks[2].color, 0.7, 0.005);
        publicBooksColor = ofLerp(publicBooksColor, 0.6, 0.005);
    }
    
    //  Some physics to move the particles
    //
    for (int i = 0; i < publicBooks.size(); i++) {

        //  Every particle is atracted to his origin place
        //  So they tend to come back slowly
        //
        publicBooks[i].addAttractionForce(publicBooks[i].origin, 1000, 0.1);
        
        //  In the right way start moving to the destiny.
        //
        if (scale > 1.0 ){
            
            //  Adding a little of noise will make it to look interesting
            //
            publicBooks[i].addNoise(ofRandom(PI/2.0,-PI/2.0), ofRandom(0.2));
            publicBooks[i].addAttractionForce(publicBooks[i].destiny, 1000, 0.5);
        }
        
        //  After all the forces have been added update the position.
        //
        publicBooks[i].update();
        
    }
    
    //  For debugin ( can be commented )
    //
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
    
//    ofBackgroundGradient(ofColor::gray, ofColor::black);
    ofBackground(0);
    
    ofPushMatrix();
    //  Move to the middle of the screen
    //
    ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);
    
    //  Zoom
    //
    ofScale(scale, scale, 1.0);
    
    //  center the blocks
    //
    ofTranslate(-totalWith*0.5, -totalHeight*0.5);
    
    //  Camera pan
    //
    ofTranslate(translate.x, translate.y);
    
    //  Draw black book boxes
    //
    for (int i = 0; i < 4; i++) {
        archiveBooks[i].draw();
    }
    
    //  Draw the particles
    //
    glBegin(GL_POINTS);
    ofPushStyle();
    ofSetColor(ofFloatColor(publicBooksColor));
    
    for (int i = 0; i < publicBooks.size(); i++) {
        glVertex3f(publicBooks[i].x,
                   publicBooks[i].y,
                   publicBooks[i].z);
    }
    ofPopStyle();
    glEnd();
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f'){
        ofToggleFullscreen();
    } else if (key == ' '){
        bZoomOut = !bZoomOut;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    makeScene();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}