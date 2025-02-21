
#include "ParticleEmitter.h"
#include "raylib.h"
#include <algorithm>
#include <utility>
#include "Number.h"
#include "Random.h"

ParticleEmitter::ParticleEmitter(Vector2 position, int numberOfParticles):position{std::move(position)}{
 for(int i = 0; i < numberOfParticles; ++i){
    particles.push_back(Particle{Vector2{position.x + 0, position.y + 0}, Vector2{randomFloat(-5, 5), randomFloat(-5, 0)}, Vector2{0,0}, .5, randomColor(), randomFloat(10, 400)});
  } 
}

ParticleEmitter::ParticleEmitter(Vector2 position, std::vector<Particle> particles):position{std::move(position)}, particles{std::move(particles)}{}

void ParticleEmitter::Init(){}

void ParticleEmitter::Update(double dt){

  for(int i = 0; i < particles.size(); ++i){
    if(particles[i].delay <= 0){

      particles[i].ApplyForce(acceleration);
    }
      particles[i].Update(dt);
    
  }

  acceleration *= 0;
}

void ParticleEmitter::ApplyForce(Vector2 force){
  acceleration += force;
}

void ParticleEmitter::Draw(){

    for(int i = 0; i < particles.size(); ++i){
      particles[i].Draw();
      
    }
}
