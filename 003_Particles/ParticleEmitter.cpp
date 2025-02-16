
#include "ParticleEmitter.h"
#include "raylib.h"
#include <algorithm>
#include <utility>

ParticleEmitter::ParticleEmitter(Vector2 position, int numberOfParticles):position{std::move(position)}{
 for(int i = 0; i < numberOfParticles; ++i){
    if(i % 2 == 0){

      particles.push_back(Particle{Vector2{position.x + (i * 32), 0}, .25, PURPLE, (float)i*100});
    }else{

      particles.push_back(Particle{Vector2{position.x - (i * 32), 0}, .25, PURPLE, (float)i*100});
    }
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
