#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"


int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);			// <-------- setup the GL context

	ofRunApp(new testApp());
}
