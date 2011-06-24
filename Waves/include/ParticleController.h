#pragma once

#include "Particle.h"
#include "cinder/Perlin.h"
#include <list>

class ParticleController {
  public:
	ParticleController() {}

	void update(const ci::Perlin& perlin, float deltaTime);
	void draw();

	void addParticles(const ci::Vec2f& position, const ci::Vec2f& velocity, float amountPerSecond, float deltaTime);

  private:
	std::list<Particle>	particles_;
};
