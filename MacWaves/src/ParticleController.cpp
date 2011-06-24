#include "ParticleController.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace std;

void ParticleController::update(const Perlin& perlin, float deltaTime) {
	for (list<Particle>::iterator it = particles_.begin(); it != particles_.end(); ) {
        if (it->update(perlin, deltaTime)) {
            ++it;
        } else {
			it = particles_.erase(it);
		}
	}
}

void ParticleController::draw() {
	for (list<Particle>::iterator it = particles_.begin(); it != particles_.end(); ++it) {
		it->draw();
	}
}

void ParticleController::addParticles(const Vec2f& position, const Vec2f &velocity, float amountPerSecond, float deltaTime) {
    float amountPerFrame = amountPerSecond * deltaTime;
    int amount = floor(amountPerFrame);
    if (Rand::randFloat() < amountPerFrame - amount) amount++;
    
    for (int i = 0; i < amount; ++i) {
		particles_.push_back(Particle(position, velocity));
	}
}
