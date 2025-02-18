#ifndef PARTICLES_PARTICLE_H_
#define PARTICLES_PARTICLE_H_

#include "Body.h"
class Particle: public Body{
public:
  Particle(Vector2 position = Vector2{0,0}, Vector2 velocity = Vector2{0,0}, Vector2 acceleration = Vector2{0,0}, float mass = 10.f, Color color = RED, float delay = 10.f);
  Particle(Vector2 position = Vector2{0,0},  float mass = 10.f, Color color = RED, float delay = 10.f);
  
  void Reset();
  void Update(float dt);
  void Draw();

  float delay;
private:
  const float startingX;
  const float startingY;
  const int startingLifeSpan = 255;
  const float startingDelay;
  const Vector2 startingVelocity;

  int lifeSpan = 255;
};

#endif
