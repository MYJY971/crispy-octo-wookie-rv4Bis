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
        bool compareRectPoints(ofRectangle R1, ofRectangle R2);
        void drawBlob(ofxCvBlob * blob, float x = 0, float y = 0);

        ofVideoGrabber cam;
        ofVideoPlayer player;

        ofBaseVideoDraws * video;
        ofBaseVideoDraws * videoTest;
        ofxAruco aruco;
        ofxCvContourFinder contour;
        int img_width, img_height;

        ofxCvColorImage img;
        ofxCvColorImage img2;
        ofxCvColorImage hsvImg;
        float hue;
        float sat;
        float bright;
        int tolerance;
        ofxCvGrayscaleImage grayImg0;
        ofxCvGrayscaleImage grayImg;
        ofxCvGrayscaleImage grayImg2;
        ofxCvGrayscaleImage grayImg3;
        ofxCvGrayscaleImage grayImg4;

        ofxCvBlob biggestBlob;
        bool updateImg;
        ofPolyline polygoneContour;
        ofRectangle boards;
        ofRectangle bbox;



        ofColor targetColorHsv;
        ofImage videoImage;

        ofxCvGrayscaleImage image;
};
