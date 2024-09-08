#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "SpoutSender.h"

#include <string>

namespace cinder {

	class SpoutOut {
	public:
		SpoutOut( const std::string& name, const ivec2& size )
			: mSize{ size }
			, mName{ name }
		{
			// Option
			// Give the sender a name 
			// If no name is specified, the application name is used
			mSpoutSender.SetSenderName(mName.c_str());
		}

		~SpoutOut() {
			// Close the sender on exit
			mSpoutSender.ReleaseSender();
		}

		void sendViewport() {
			//
			// Send fbo
			// 
			// The default framebuffer is used if Fbo ID is zero
			// If the size is also zero, the viewport dimensions are used
			// Here the size is saved in a global variable for getSize() query
			//
			mSize = app::getWindowSize();
			mSpoutSender.SendFbo(0, mSize.x, mSize.y);
		}

		glm::ivec2				getSize() const { return mSize; }
		std::string				getName() const { return mName; }
		SpoutSender&			getSpoutSender() { return mSpoutSender; }
		const SpoutSender&		getSpoutSender() const { return mSpoutSender; }

	private:

		std::string			mName;
		glm::uvec2			mSize;
		SpoutSender			mSpoutSender; // Create a Spout receiver object

	};

} // end namespace ci

