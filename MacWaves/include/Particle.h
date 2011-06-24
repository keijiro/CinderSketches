#pragma once

#include "cinder/Vector.h"
#include "cinder/Perlin.h"

class Particle {
  public:
	Particle() {};
	Particle(ci::Vec2f position, ci::Vec2f velocity);
    
	bool update(const ci::Perlin& perlin, float deltaTime);
	void draw();
    
  private:
	ci::Vec2f position_;
	ci::Vec2f velocity_;
	
	float decay_;
	float scale_;
	
    float lifespan_;
    float time_;
};
