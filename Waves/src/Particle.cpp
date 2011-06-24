#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Particle::Particle(Vec2f position, Vec2f velocity) {
    position_ = position;
    velocity_ = velocity + Rand::randVec2f() * Rand::randFloat(0.5f, 2.0f);
    
    decay_ = Rand::randFloat(0.96f, 0.99f);
	scale_ = 6.0f;
    
	lifespan_ = Rand::randFloat(1.0f, 5.0f);
    time_ = 0.0f;
}	

bool Particle::update(const Perlin &perlin, float deltaTime) {
	float nX = position_.x * 0.005f;
	float nY = position_.y * 0.005f;
	float nZ = app::getElapsedSeconds() * 0.1f;
	float noiseAngle = perlin.fBm(nX, nY, nZ) * 15.0f;
	Vec2f noiseVector(cos(noiseAngle), sin(noiseAngle));

	velocity_ += noiseVector * 0.2f * time_ / lifespan_;
	position_ += velocity_;
    velocity_ *= decay_;
    
    time_ += deltaTime;
    return time_ < lifespan_;
}

void Particle::draw() {
    const float percent = 1.0f - time_ / lifespan_;
	gl::drawSolidCircle(position_, scale_ * percent * percent);
}
