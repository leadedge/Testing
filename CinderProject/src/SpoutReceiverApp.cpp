/*

Basic Spout receiver for Cinder

Uses the Spout SDK
https://github.com/leadedge/Spout2
Copyright (C) 2024 Lynn Jarvis.

03-03-17 - Spout 2.006
08-09-24 - Spout 2.007

*/

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

#include "CiSpoutIn.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SpoutReceiverApp : public App {
public:
	void draw() override;
	void mouseDown(MouseEvent event) override;

	SpoutIn	mSpoutIn;
};


void SpoutReceiverApp::draw()
{
	gl::clear();

	auto tex = mSpoutIn.receiveTexture();
	if (tex) {

		// Draw the texture and fill the screen
		gl::draw(tex, getWindowBounds());

		// Show the user what it is receiving
		gl::ScopedBlendAlpha alpha;
		gl::enableAlphaBlending();
		gl::drawString("Receiving from: " + mSpoutIn.getSenderName(), vec2(toPixels(20), toPixels(20)), Color(1, 1, 1), Font("Verdana", toPixels(24)));
		gl::drawString("fps: " + std::to_string((int)getAverageFps()), vec2(getWindowWidth() - toPixels(100), toPixels(20)), Color(1, 1, 1), Font("Verdana", toPixels(24)));
		gl::drawString("Right click to select a sender", vec2(toPixels(20), getWindowHeight() - toPixels(40)), Color(1, 1, 1), Font("Verdana", toPixels(24)));
	}
	else {
		gl::ScopedBlendAlpha alpha;
		gl::enableAlphaBlending();
		gl::drawString("No sender detected", vec2(toPixels(20), toPixels(20)), Color(1, 1, 1), Font("Verdana", toPixels(24)));
	}
}
void SpoutReceiverApp::mouseDown(MouseEvent event)
{
	if (event.isRightDown()) { // Select a sender
		mSpoutIn.getSpoutReceiver().SelectSender(); 
	}
}

void prepareSettings(App::Settings *settings)
{
	settings->setWindowSize(640, 480);
}

// This line tells Cinder to actually create the application
CINDER_APP(SpoutReceiverApp, RendererGl, prepareSettings)
