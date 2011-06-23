#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class MacWavesApp : public AppBasic {
  public:
    void prepareSettings(Settings *settings);
	void update();
	void draw();
    
    std::list<Path2d> mPaths;
};

void MacWavesApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize(384, 512);
}

void MacWavesApp::update()
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

void MacWavesApp::draw()
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

CINDER_APP_BASIC(MacWavesApp, RendererGl)
