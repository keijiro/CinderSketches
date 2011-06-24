#include "ParticleController.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

namespace {
    float easeOut(float value, float target, float coeff, float delta) {
        return target - (target - value) * exp(coeff * delta);
    }
}

class MacWavesApp : public AppBasic {
  public:
    void prepareSettings(Settings* settings);

    void mouseDown(MouseEvent event);
    void mouseUp(MouseEvent event);

    void setup();
	void update();
	void draw();

    Vec2i prevMousePos_;
    float prevTime_;

    Perlin perlin_;

    ParticleController particleController_;
    bool emit_;

    std::list<Path2d> paths_;
    float waveHeight;
};

void MacWavesApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(384, 512);
}

void MacWavesApp::mouseDown(MouseEvent event) {
    emit_ = true;
}

void MacWavesApp::mouseUp(MouseEvent event) {
    emit_ = false;
}

void MacWavesApp::setup() {
    prevTime_ = getElapsedSeconds();
    prevMousePos_ = getMousePos();
	perlin_ = Perlin();
    emit_ = false;
    waveHeight = 0.0f;
}

void MacWavesApp::update() {
    const float time = getElapsedSeconds();
    const float deltaTime = time - prevTime_;

    const float sw = getWindowWidth();
    const float sh = getWindowHeight();
    
    const float timeScale = 0.3f;
    const float timeOffset = 100.0f;
    
    if (emit_) {
        waveHeight = easeOut(waveHeight, 2.5f, -2.0f, deltaTime);
        particleController_.addParticles(getMousePos(), getMousePos() - prevMousePos_, 6.6, deltaTime);
    } else {
        waveHeight = easeOut(waveHeight, 0.6f, -1.0f, deltaTime);
    }

    particleController_.update(perlin_, deltaTime);

    paths_.clear();
    
    for (int i = 0; i < 20; ++i) {
        float t = time * timeScale + timeOffset;

        for (int j = 0; j < 3; ++j) {
            paths_.push_back(Path2d());
            Path2d& path = paths_.back();
    
            float y1 = sin(t * 0.21f) * 0.6f;
            float y2 = sin(t * (1.91f + 0.013f * i));
            float y3 = sin(t * (1.03f + 0.031f * i));
            float y4 = sin(t * 0.31f) * 0.6f;
            
            path.moveTo(-0.20f * sw, sh * (y1 * waveHeight + 1.0f) * 0.5f);
            path.curveTo(0.33f * sw, sh * (y2 * waveHeight + 1.0f) * 0.5f,
                         0.66f * sw, sh * (y3 * waveHeight + 1.0f) * 0.5f,
                         1.20f * sw, sh * (y4 * waveHeight + 1.0f) * 0.5f);
            
            t += 0.1f;
        }
    }
    
    prevMousePos_ = getMousePos();
    prevTime_ = time;
}

void MacWavesApp::draw() {
	gl::clear(Color(1, 1, 1), true); 
    
    glDisable(GL_TEXTURE_2D);
    gl::enableAlphaBlending();
    
    float numPath = paths_.size();
    int i = 0;
    for (std::list<Path2d>::const_iterator it = paths_.begin(); it != paths_.end(); ++it, ++i) {
        gl::color(ColorA(0.0f, 0.3f * i / numPath, 0.5f * i / numPath, 0.3f));
        gl::draw(*it);
    }

    gl::color(ColorA(0.0f, 0.0f, 0.2f, 0.2f));
    particleController_.draw();
}

CINDER_APP_BASIC(MacWavesApp, RendererGl)
