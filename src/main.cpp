#include "ofMain.h"
#include "gameCore.h"
#include "ofAppGlutWindow.h"


//========================================================================

int main() {

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280,720, OF_WINDOW); // OF_WINDOW or OF_FULLSCREEN

	ofRunApp(new gameCore());

}
