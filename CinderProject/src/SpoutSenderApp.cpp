/*

Basic Spout sender for Cinder

Uses the Spout SDK
https://github.com/leadedge/Spout2
Copyright (C) 2014-2024 Lynn Jarvis.

03-03-17 - Spout 2.006 release
08-09-24 - Spout 2.007 release


*/
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/GeomIo.h"
#include "cinder/CameraUi.h"
#include "cinder/Camera.h"

#include "CiSpoutOut.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SpoutSenderApp : public App {
public:
	SpoutSenderApp();
	void mouseDrag(MouseEvent event) override;
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void update() override;
	void draw() override;
	void resize() override;

	gl::BatchRef	mBatch;

	CameraPersp		mCamera;
	CameraUi		mCameraUi;

	SpoutOut		mSpoutOut;
};

SpoutSenderApp::SpoutSenderApp()
	: mCameraUi(&mCamera)
	, mSpoutOut("Cinder Spout Sender", app::getWindowSize())
{
	// The sender name can be different to the application
	// If no name is specified, the application name is used
	 
	// Set window title to match the sender name
	app::getWindow()->setTitle("Cinder Spout Sender");

	auto teapot = geom::Teapot() >> geom::Scale(vec3(10));
	mBatch = gl::Batch::create(teapot, gl::getStockShader(gl::ShaderDef().lambert()));

	gl::enableDepth();

}

void SpoutSenderApp::mouseDrag(MouseEvent event)
{
	mCameraUi.mouseDrag(event);
}

void SpoutSenderApp::mouseDown(MouseEvent event)
{
	mCameraUi.mouseDown(event);
}

void SpoutSenderApp::mouseUp(MouseEvent event)
{
	mCameraUi.mouseUp(event);
}

void SpoutSenderApp::update()
{
}

void SpoutSenderApp::draw()
{
	gl::clear(Color(0, 0, 0));
	gl::setMatrices(mCamera);
	mBatch->draw();

	mSpoutOut.sendViewport();
}

void SpoutSenderApp::resize()
{
	mCamera.setAspectRatio(app::getWindowAspectRatio());
}

CINDER_APP(SpoutSenderApp, RendererGl{ RendererGl::Options().msaa(16) })
