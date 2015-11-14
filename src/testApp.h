#pragma once

#include "ofMain.h"
#include "ofxAruco.h"
#include "ofxCvContourFinder.h"
#include "ofxCvHaarFinder.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofVideoGrabber cam;
		ofVideoPlayer player;

		ofBaseVideoDraws * video;
        ofBaseVideoDraws * videoTest;
		ofxAruco aruco;

        int img_width, img_height;
        ofxCvColorImage img;

        ofxCvColorImage hsvImg;
        float hue;
        float sat;
        float bright;
        int tolerance;
        ofxCvGrayscaleImage grayImg;
        ofColor targetColorHsv;

        ofxCvGrayscaleImage image;
};
