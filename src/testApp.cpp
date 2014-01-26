#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //voronoi
//	ofBackground(191,191,191);
    
	xValues.push_back(mouseX-ofGetWidth()/2);
	yValues.push_back(mouseY-ofGetHeight()/2);
	count = 1;
    
    //jaggy line
    ofSetFullscreen(true);
    for (int i =0; i<1000; i++) {
        randomVector.push_back(ofRandom(-1, 1));
    }
}

//--------------------------------------------------------------
void testApp::update(){
	vdg.generateVoronoi(xValues,yValues,count, -ofGetWidth()/2,ofGetWidth()/2,-ofGetHeight()/2,ofGetHeight()/2,3);
	vdg.resetIterator();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor(255), ofColor(0));
    
    ofSetColor(0, 90, 60);
	
	ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate()), 10, 10);
//	
//	ofPushMatrix();
//	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
	
//	ofFill();
//	for(int i=0; i<count; i++) {
//		ofCircle(xValues[i], yValues[i], 5);
//	}
//	ofPopMatrix();
	
	
	float x1,y1,x2,y2;
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    ofPushStyle();
    ofSetColor(255);
	while(vdg.getNext(x1,y1,x2,y2))
	{
//		ofLine(x1, y1, x2, y2);
        noiseLine(x1, y1, x2, y2, 3, 50);
	}
    ofPopStyle();
	ofPopMatrix();
}


void testApp::noiseLine(float x1, float y1, float x2, float y2, float amplitude, float lineNumber){
    //(x1,y1)=始点
    //(x2,y2)=終点
    //amplitude=振幅
    //lineNumber=線分の数
    
    float distance = sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
    
    vector<ofPoint> noisePointVector;
    float X, Y;
    for (int i = 0; i<=lineNumber; i++) {
        if (i == 0 || i == lineNumber) {
            X = i/lineNumber*(x2-x1)+x1;
            Y = i/lineNumber*(y2-y1)+y1;
        }else{
            X = i/lineNumber*(x2-x1)-(y2-y1)/distance*amplitude*randomVector[i]+x1;
            Y = i/lineNumber*(y2-y1)+(x2-x1)/distance*amplitude*randomVector[i]+y1;
        }
        noisePointVector.push_back(ofPoint(X, Y));
    }
    
    for (int i = 0; i<noisePointVector.size(); i++) {
//        ofPushStyle();
//        ofSetColor(255, 0, 0);
        
        if (i > 0) {
            ofLine(noisePointVector[i-1].x, noisePointVector[i-1].y, noisePointVector[i].x, noisePointVector[i].y);
        }
//        ofPopStyle();
    }
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    xValues.push_back(ofRandom(-ofGetWidth()/2+10, ofGetWidth()/2-10));
	yValues.push_back(ofRandom(-ofGetHeight()/2+10,ofGetHeight()/2-10));
	count++;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    xValues[0] = (x-ofGetWidth()/2);
	yValues[0] = (y-ofGetHeight()/2);
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
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
