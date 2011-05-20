#include "Cinder/Cinder.h"
#include "cinder/Channel.h"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/MovieWriter.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;

class CloudChamberApp : public AppBasic {
public:
    void prepareSettings(Settings *settings);
	void setup();
	void mouseDown(MouseEvent event);
	void update();
	void draw();
    
	ParticleController mParticleController;
    Perlin mPerlin;
    Path2d mPath;
    
    qtime::MovieWriter mMovieWriter;
};

void CloudChamberApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize(512, 256);
}

void CloudChamberApp::setup()
{
	mPerlin = Perlin();
    
	qtime::MovieWriter::Format format;
	if (qtime::MovieWriter::getUserCompressionSettings(&format)) {
		mMovieWriter = qtime::MovieWriter(getDocumentsDirectory() + "output.mov", getWindowWidth(), getWindowHeight(), format);
	}
}

void CloudChamberApp::mouseDown( MouseEvent event )
{
}

void CloudChamberApp::update()
{
    if (!mMovieWriter) return;
    
    float sw = getWindowWidth();
    float sh = getWindowHeight();
    
    if (Rand::randFloat() < 0.2f) {
        mParticleController.addParticles(1, Vec2f(sw * 0.5f, sh * 0.5f), Vec2f::zero());
        mParticleController.addParticles(1, Vec2f(sw * 0.5f, sh * 0.5f), Vec2f::zero());
    }
    
	mParticleController.update(mPerlin, Vec2f(sw * 0.5f, sh * 0.5f));
    
    mPath.clear();
    
    std::list<Particle>::const_iterator pit = mParticleController.mParticles.begin();
    mPath.moveTo(Vec2f(sw * 0.5f, sh * 0.5f));
    while (true) {
        if (++pit == mParticleController.mParticles.end()) break;
        Vec2f pt1 = pit->mLoc;
        if (++pit == mParticleController.mParticles.end()) break;
        Vec2f pt2 = pit->mLoc;
        mPath.quadTo(pt1, pt2);
    }
}

void CloudChamberApp::draw()
{
	gl::clear(Color(0, 0, 0), true); 
    glDisable(GL_TEXTURE_2D);
    mParticleController.draw();
    gl::draw(mPath);
    
	if (mMovieWriter) mMovieWriter.addFrame(copyWindowSurface());
}

CINDER_APP_BASIC(CloudChamberApp, RendererGl)
