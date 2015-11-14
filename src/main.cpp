#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 1280,480, OF_WINDOW);
    ofSetWindowTitle("RV TD4");

	ofRunApp( new testApp());
}
