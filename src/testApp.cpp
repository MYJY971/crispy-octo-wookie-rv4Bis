#include "testApp.h"
#include "ofxCv.h"
#include "ofBitmapFont.h"

int tolerance = 30;

//--------------------------------------------------------------
void drawMarker(float size, const ofColor & color){
    ofDrawAxis(size);
    ofPushMatrix();
        // move up from the center by size*.5
        // to draw a box centered at that point
        ofTranslate(0,size*0.5,0);
        ofFill();
        ofSetColor(color,50);
        ofBox(size);
        ofNoFill();
        ofSetColor(color);
        ofBox(size);
    ofPopMatrix();
}
//--------------------------------------------------------------
void testApp::setup(){

    string boardName = "boardConfiguration.yml";
    ofSetVerticalSync(true);
    img_width = 640;
    img_height = 480;
    cam.setDeviceID(0);
    cam.setDesiredFrameRate(30.0);
    cam.initGrabber(640,480);
    video = &cam;

    img.allocate(img_width,img_height);

    hsvImg.allocate(img_width, img_height);
    grayImg.allocate(img_width,img_height);
    image.allocate(img_width, img_height);


    // TODO: initialize ArUco
    aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);

    std::cout<< "w=" << video->getWidth() << std::endl;
    
    

    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){
    video->update();
    if(video->isFrameNew()){
        // TODO: detect board
        aruco.detectBoards(video->getPixelsRef());


        img.setFromPixels(cam.getPixelsRef());
        img.mirror(false,true);

        //img.convertRgbToHsv();
        hsvImg = img;
        hsvImg.convertRgbToHsv();

        image=img;

        for (int j =0; j<img_height; ++j)
        {
            for (int i=0; i<img_width ; ++i)
            {
              if( (ofInRange(hsvImg.getPixelsRef().getColor(i,j).getHue(), hue-tolerance, hue+tolerance)) &&
                  (ofInRange(hsvImg.getPixelsRef().getColor(i,j).getSaturation(), sat-tolerance, sat+tolerance)) &&
                  (ofInRange(hsvImg.getPixelsRef().getColor(i,j).getBrightness(), bright-tolerance, bright+tolerance))   )

                  grayImg.getPixelsRef().setColor(i,j,ofColor::white);


              else
                  grayImg.getPixelsRef().setColor(i,j,ofColor::black);

            }
        }

        grayImg.flagImageChanged();

    }

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255);
    video->draw(0,0);

    //videoTest->draw(0,0);

    // TODO: draw detected markers and board
for(int i=0;i<aruco.getNumMarkers();i++){
            aruco.begin(i);
            ofDrawAxis(0.2);
            //drawMarker(0.15,ofColor::white);
            aruco.end();
        }

if(aruco.getBoardProbability()>0.2){
        for(int i=0;i<aruco.getNumBoards();i++){
            aruco.beginBoard(i);
            ofSetColor(ofColor::red,75);
            ofDrawBox(0.5,0.5,0.5);
            aruco.end();
        }
    }


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
