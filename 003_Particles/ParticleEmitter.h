#ifndef PARTICLES_PARTICLE_EMITTER_H_
#define PARTICLES_PARTICLE_EMITTER_H_


#include "Particle.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>
class ParticleEmitter{
public:
  ParticleEmitter(Vector2 position, int numberOfParticles);
  ParticleEmitter(Vector2 position, std::vector<Particle> particles);
  
  void Init();
  void Update(double dt);
  void Draw();
  void ApplyForce(Vector2 force);


private:
  std::vector<Particle> particles{};
  Vector2 position;
  Vector2 acceleration = Vector2{0.0};
};

#endif // !PARTICLES_PARTICLE_EMITTER_H_

