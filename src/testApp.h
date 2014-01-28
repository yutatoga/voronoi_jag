#pragma once

#include "ofMain.h"
#include "VoronoiDiagramGenerator.h"

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
		
    //jaggy line
    void noiseLine(float x1, float y1, float x2, float y2, float amplitude, float lineNumber);

    vector<float> randomVector;
    
    //voronoi
	VoronoiDiagramGenerator vdg;
	
	vector<float> xValues;
	vector<float> yValues;
    
    //上からかぶせる陰画像
    ofImage shadowImage;
	
	//count
	int counter;
    
};
