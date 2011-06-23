#include "cinder/app/AppCocoaTouch.h"
#include "cinder/app/Renderer.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "cinder/gl/gl.h"

#include <list>

using namespace ci;
using namespace ci::app;

class WavesApp : public AppCocoaTouch {
  public:
	virtual void	setup();
	virtual void	resize( ResizeEvent event );
	virtual void	update();
	virtual void	draw();
	virtual void	mouseDown( MouseEvent event );

    std::list<Path2d> mPaths;
};

void WavesApp::setup()
{
}

void WavesApp::resize( ResizeEvent event )
{
}

void WavesApp::mouseDown( MouseEvent event )
{
	console() << "Mouse down @ " << event.getPos() << std::endl;
}

void WavesApp::update()
{
    float time = getElapsedSeconds() * 0.66f + 10.0f;
    float sw = getWindowWidth();
    float sh = getWindowHeight();
    
    mPaths.clear();
    
    for (int i = 0; i < 32; ++i) {
        mPaths.push_back(Path2d());
        Path2d& path = mPaths.back();
        path.moveTo(Vec2f(-0.2f * sw, sh * (sin(time * 0.21f) * 0.3f + 1.0f) * 0.5f));
        path.curveTo(0.33f * sw, sh * (sin(time * 1.71f *(1.0f + 0.002f * i)) * 1.5f + 1.0f) * 0.5f,
                     0.66f * sw, sh * (sin(time * 1.01f *(1.0f + 0.005f * i)) * 1.5f + 1.0f) * 0.5f,
                     1.20f * sw, sh * (sin(time * 0.23f) * 0.3f + 1.0f) * 0.5f);
    }
}

void WavesApp::draw()
{
	gl::clear(Color(1, 1, 1), true); 
    glDisable(GL_TEXTURE_2D);
    gl::enableAlphaBlending();
    for (std::list<Path2d>::const_iterator it = mPaths.begin();
         it != mPaths.end(); ++it) {
        gl::color(ColorA(0.0f, 0.0f, 0.1f, 0.5f));
        gl::draw(*it);
    }
}

CINDER_APP_COCOA_TOUCH( WavesApp, RendererGl )
