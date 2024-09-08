#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Log.h"

// SPOUT
#include "SpoutReceiver.h"

namespace cinder {

class SpoutIn {
public:
	SpoutIn()
		: mSize{640, 480}
		, mTexture{ nullptr }
	{
		mTexture = gl::Texture2d::create(mSize.x, mSize.y, gl::Texture::Format().loadTopDown());
	}
	~SpoutIn() {
		mSpoutReceiver.ReleaseReceiver();
	}

	gl::Texture2dRef receiveTexture() {
		// Receive to a texture
		// Specify Invert option - OpenGL and DirectX have different texture origins.
		if (mSpoutReceiver.ReceiveTexture(mTexture->getId(), mTexture->getTarget(), true)) {
			if (mSpoutReceiver.IsUpdated()) {
				// Update the receiving texture if the sender size has changed
				mTexture.reset();
				mTexture = gl::Texture2d::create(mSpoutReceiver.GetSenderWidth(), mSpoutReceiver.GetSenderHeight());
				// Update local global variables
				mSize = glm::uvec2(mSpoutReceiver.GetSenderWidth(), mSpoutReceiver.GetSenderHeight());
				strcpy_s(mSenderName, 256, mSpoutReceiver.GetSenderName());
			}
			return mTexture;
		}
		return nullptr;
	}

	glm::ivec2				getSize() const { return mSize; }
	std::string				getSenderName() const { return mSenderName; }
	SpoutReceiver&			getSpoutReceiver() { return mSpoutReceiver; }
	const SpoutReceiver&	getSpoutReceiver() const { return mSpoutReceiver; }

private:

	char				mSenderName[256];
	glm::uvec2			mSize;
	gl::TextureRef		mTexture;
	SpoutReceiver		mSpoutReceiver; // Create a Spout receiver object

};

} // end namespace ci