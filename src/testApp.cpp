#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFullscreen(true);
	counter = 0;
    //voronoi
//	ofBackground(191,191,191);
    
	int voronoiNumber = 100;
    
//	ofLog(OF_LOG_NOTICE, ofToString(sin(pi/2)));
//    for (int i = 0; i<voronoiNumber; i++) {
		//完全ランダム
//        xValues.push_back(ofRandom(-ofGetWidth()/2+10, ofGetWidth()/2-10));
//        yValues.push_back(ofRandom(-ofGetHeight()/2+10,ofGetHeight()/2-10));
		
		//逆になった
//        float thetaX = ofRandom(0, 2*pi);
//		xValues.push_back(sin(ofRandom(0, 2*pi)-pi/2.0)*ofGetWidth()/3.0);
//
//		float thetaY = ofRandom(0, 2*pi);
//        yValues.push_back(sin(ofRandom(0, 2*pi)-pi/2.0)*ofGetHeight()/3.0);
		
		//サイン波を使う
//		float theta = ofRandom(0, 2*pi);
//		float amplitude = 1000*pow(ofRandom(0,1), 2);
//		xValues.push_back(sin(theta)*amplitude);
//		yValues.push_back(cos(theta)*amplitude);
		
//    }
    
    //jaggy line
    for (int i =0; i<1000; i++) {
        randomVector.push_back(ofRandom(-1, 1));
    }
    
    //陰の画像
    //α値を使用する
    ofEnableAlphaBlending();
//    shadowImage.loadImage("shadow_75_50.png");
//    shadowImage.loadImage("mona.jpg")fffffffffff;
}

//--------------------------------------------------------------
void testApp::update(){
	if (xValues.size() != 0) {
		vdg.generateVoronoi(xValues, yValues, xValues.size(), -ofGetWidth()/2,ofGetWidth()/2,-ofGetHeight()/2,ofGetHeight()/2,3);
		vdg.resetIterator();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
    ofBackgroundGradient(ofColor(255), ofColor(0));
	
	ofDrawBitmapString("fps   : "+ofToString(ofGetFrameRate()), 10, 50);
    ofDrawBitmapString("point : "+ofToString(xValues.size()), 10, 60);
	ofDrawBitmapString("couner: "+ofToString(counter), 10, 70);
	
	if (xValues.size() != 0) {
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
		ofFill();
		ofPushStyle();
		ofSetColor(255, 127, 127);
		for(int i=0; i<xValues.size(); i++) {
			ofCircle(xValues[i], yValues[i], 5);
		}
		ofPopStyle();
		ofPopMatrix();
		
		
		float x1,y1,x2,y2;
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
		ofPushStyle();
		ofSetColor(255);
		while(vdg.getNext(x1,y1,x2,y2))
		{
			//      線分
			//		ofLine(x1, y1, x2, y2);
			//ギザギザ線
			if (ofDist(x1, y1, 0, 0) < counter) {
				noiseLine(x1, y1, x2, y2, 3, 50);
			}
		}
		ofPopStyle();
		ofPopMatrix();
	}

//影の円形グラーデーション画像を重ねてひびが広がるのを試す >> 失敗につき、コメントアウト
//    float oneSize = ofGetWidth()*count/3;
//    shadowImage.draw((ofGetWidth()-oneSize)/2.0f, (ofGetHeight()-oneSize)/2.0f, oneSize, oneSize);
    
    
    
    //guideline
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofLine(ofGetWidth()/2.0f, 0, ofGetWidth()/2.0f, ofGetHeight());
    ofLine(0, ofGetHeight()/2.0f, ofGetWidth(), ofGetHeight()/2.0f);
    ofPopStyle();
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
	counter += 10;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if (xValues.size() != 0) {
		xValues[0] = (x-ofGetWidth()/2);
		yValues[0] = (y-ofGetHeight()/2);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	int voronoiNumber = ofRandom(10, 100);
	for (int i = 0; i<voronoiNumber; i++) {
		//サイン波を使う
		float theta = ofRandom(0, 2*pi);
		float amplitude = 100*pow(ofRandom(0,1), 2);
		xValues.push_back(sin(theta)*amplitude+x-ofGetWidth()/2.0);
		yValues.push_back(cos(theta)*amplitude+y-ofGetHeight()/2.0);
	}
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
