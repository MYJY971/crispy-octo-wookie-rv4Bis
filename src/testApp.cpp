#include "testApp.h"
#include "ofxCv.h"
#include "ofBitmapFont.h"

int tolerance = 30;
ofxCvBlob theBlob;

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
    cam.initGrabber(img_width,img_height);
    video = &cam;

    img.allocate(img_width,img_height);
    img2.allocate(img_width,img_height);

    hsvImg.allocate(img_width, img_height);
    grayImg0.allocate(img_width,img_height);
    grayImg.allocate(img_width,img_height);
    grayImg2.allocate(img_width,img_height);
    grayImg3.allocate(img_width,img_height);
    grayImg4.allocate(img_width,img_height);
    image.allocate(img_width, img_height);
    videoImage.allocate(img_width, img_height,OF_IMAGE_COLOR);

    updateImg=true;
    boards=ofRectangle(0,0,0,0);

    // TODO: initialize ArUco
    aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);

    std::cout<< "w=" << video->getWidth() << std::endl;


    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){



    video->update();
    if(video->isFrameNew()){

        ofPixels pixels;
        ofPixels alphaPixels;
        cam.getTextureReference().readToPixels(pixels);
        alphaPixels.allocate(pixels.getWidth(),pixels.getHeight(),OF_PIXELS_RGBA);
        // TODO: detect board
        aruco.detectBoards(video->getPixelsRef());


        img.setFromPixels(cam.getPixelsRef());
        //img.mirror(false,true);

        //img.convertRgbToHsv();
//        if(updateImg)
//            img2=img;

//        hsvImg = img;
//        hsvImg.convertRgbToHsv();

        grayImg=img;
        hsvImg = grayImg;
        hsvImg.convertRgbToHsv();

        grayImg0=img;



//        for (int j=0; j<img_height;++j)
//        {
//            for(int i=0; i<img_width;++i)
//            {
//                if( ofInRange(hsvImg.getPixelsRef().getColor(i,j).getHue(),0,90))
//                {

//                  grayImg0.getPixelsRef().setColor(i,j,ofColor::white);


//                }
//                else
//                    grayImg0.getPixelsRef().setColor(i,j,ofColor::black);


//            }
//        }
         grayImg2=grayImg0;
         grayImg0.invert();


        for(int i=0; i<6; ++i)
           grayImg0.dilate_3x3();

        for(int i=0; i<6; ++i)
           grayImg2.dilate_3x3();



        grayImg3 = img;
        for (int j =0; j<img_height; ++j)
        {
            for (int i=0; i<img_width ; ++i)
            {

                if( ofInRange(hsvImg.getPixelsRef().getColor(i,j).getBrightness(),0,50))
                {

                  grayImg3.getPixelsRef().setColor(i,j,ofColor::white);


                }


                else
                {
                  if( ofInRange(hsvImg.getPixelsRef().getColor(i,j).getBrightness(),150,255))
                      grayImg3.getPixelsRef().setColor(i,j,ofColor::white);
                  else
                      grayImg3.getPixelsRef().setColor(i,j,ofColor::black);


                 }


            }
        }

        grayImg3.dilate_3x3();
        grayImg3.flagImageChanged();



        contour.findContours(grayImg3,0,img_width*img_height,1,false);


        int lenght = 0;
        for(int i = 0; i < contour.nBlobs; i++) {

            ofxCvBlob blob = contour.blobs.at(i);
            if (blob.length > lenght)
            {
                biggestBlob=blob;
                lenght=blob.length;
            }

        }

        bbox=biggestBlob.boundingRect;

//        if( boards.getTopLeft()!=bbox.getTopLeft() && boards.getTopRight()!=bbox.getTopRight() &&
//                boards.getBottomLeft()!=bbox.getBottomLeft() && boards.getBottomRight()!=bbox.getBottomRight())
           if(compareRectPoints(boards,bbox))
           {
              updateImg=true;


           }

           if (updateImg)
           {

                polygoneContour = ofPolyline(biggestBlob.pts);
                boards=bbox;
                updateImg=false;


            }


            if(ofGetKeyPressed('u'))
            {
                  updateImg=true;
            }



        grayImg4=grayImg3;
        for (int j=0; j<img_height;++j)
        {
            for(int i=0; i<img_width;++i)
            {

//               if(!poly.inside(i,j))
//                   grayImg4.getPixelsRef().setColor(i,j,ofColor::black);
                if(!bbox.inside(i,j))
                    grayImg4.getPixelsRef().setColor(i,j,ofColor::black);
                else
                    if(!polygoneContour.inside(i,j))
                        grayImg4.getPixelsRef().setColor(i,j,ofColor::black);

            }
        }

        grayImg4.flagImageChanged();

//        for(int i=0; i<6; ++i)
//           grayImg4.dilate_3x3();
//        for(int i=0; i<6; ++i)
//           grayImg4.erode_3x3();



//        //grayImage :Image Seuillé (element superposé en blanc, le reste en noir)
//        for (int j =0; j<img_height; ++j)
//        {
//            for (int i=0; i<img_width ; ++i)
//            {

//                if( ofInRange(hsvImg.getPixelsRef().getColor(i,j).getHue(),0,90))
//                {

//                  grayImg.getPixelsRef().setColor(i,j,ofColor::black);


//                }


//                else
//                {
//                  if( ofInRange(hsvImg.getPixelsRef().getColor(i,j).getHue(),150,255))
//                      grayImg.getPixelsRef().setColor(i,j,ofColor::black);
//                  else
//                      grayImg.getPixelsRef().setColor(i,j,ofColor::white);


//                 }


//            }
//        }

//        grayImg.flagImageChanged();

        //Image occlusion
//        for (int j =0; j<pixels.getHeight()/*img_height*/; ++j)
//        {
//            for (int i=0; i<pixels.getWidth()/*img_width*/ ; ++i)
//            {

//                if(grayImg.getPixelsRef().getColor(i,j)==ofColor::black)
//                {

//                    ofColor ct= ofColor(0,0,0,0);
//                    alphaPixels.setColor(i,j,ct);

//                }
//                else
//                {

//                    ofColor c=img.getPixelsRef().getColor(i,j);
//                    alphaPixels.setColor(i,j,c);

//                }

//            }
//        }

        for (int j =0; j<pixels.getHeight()/*img_height*/; ++j)
        {
            for (int i=0; i<pixels.getWidth()/*img_width*/ ; ++i)
            {

                if(bbox.inside(i,j))
                {
                    if(polygoneContour.inside(i,j))
                    {
                        if(grayImg4.getPixelsRef().getColor(i,j)==ofColor::white)
                        {
                            ofColor ct = ofColor(0,0,0,0);
                            alphaPixels.setColor(i,j,ct);
                        }
                        else
                        {
                            ofColor c=img.getPixelsRef().getColor(i,j);
                            alphaPixels.setColor(i,j,c);
                        }
                    }
                    else
                    {
                        ofColor ct= ofColor(0,0,0,0);
                        alphaPixels.setColor(i,j,ct);
                    }
                }
                else
                {
                    ofColor ct= ofColor(0,0,0,0);
                    alphaPixels.setColor(i,j,ct);
                }
            }
        }

//        for(int i=0;i<aruco.getNumMarkers();i++){
//                    aruco.begin(i);

//                    aruco.end();
//                }



        //img2.setFromPixels(alphaPixels);
        videoImage.setFromPixels(alphaPixels);


    }



}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255);
    video->draw(0,0);
    //grayImg.draw(img_width,0);
    //grayImg4.draw(img_width,0);
    //ofRect(bbox);
    //contour.draw();

    //img2.draw(img_width,img_height);

    //grayImg4.draw(0,0);

    //drawBlob(&biggestBlob);


    //img.d
//    videoImage.draw(0,0);

    //videoTest->draw(0,0);

    //TODO: draw detected markers and board
for(int i=0;i<aruco.getNumMarkers();i++){
            aruco.begin(i);
            ofDrawAxis(0.2);
            //ofDrawPlane(0.15,0.15);

            //drawMarker(0.15,ofColor::red);
            aruco.end();
        }


if(aruco.getBoardProbability()>0.2){
        for(int i=0;i<aruco.getNumBoards();i++){
            aruco.beginBoard(i);
            ofSetColor(ofColor::red,75);
            ofDrawBox(0.5,0.5,0.5);
            //videoImage.draw(640,0);

            aruco.end();
        }
    }


ofSetColor(255);
videoImage.draw(0,0);


}


bool testApp::compareRectPoints(ofRectangle R1, ofRectangle R2)
{
    float x0 = R1.getTopLeft().x;
    float x1 = R1.getTopRight().x;
    float x2 = R1.getBottomLeft().x;
    float x3 = R1.getBottomRight().x;
    float y0 = R1.getTopLeft().y;
    float y1 = R1.getTopRight().y;
    float y2 = R1.getBottomLeft().y;
    float y3 = R1.getBottomRight().y;

    float xb0 = R2.getTopLeft().x;
    float xb1 = R2.getTopRight().x;
    float xb2 = R2.getBottomLeft().x;
    float xb3 = R2.getBottomRight().x;
    float yb0 = R2.getTopLeft().y;
    float yb1 = R2.getTopRight().y;
    float yb2 = R2.getBottomLeft().y;
    float yb3 = R2.getBottomRight().y;


    return !( ofInRange(x0+y0, xb0+yb0-10 , xb0+yb0+10) ||
             ofInRange(x1+y1, xb1+yb1-10 , xb1+yb1+10) ||
             ofInRange(x2+y2, xb2+yb2-10 , xb2+yb2+10) ||
             ofInRange(x3+y3, xb3+yb3-10 , xb3+yb3+10) ) ;

}

void testApp::drawBlob(ofxCvBlob * blob, float x, float y){
            ofFill();
            ofSetColor(ofColor::red);
            ofBeginShape();
            for (int i = 0; i < blob->nPts; i++){
                   ofVertex(x + blob->pts[i].x, y + blob->pts[i].y);
            }
            ofEndShape(true);
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
