
#include "Particle.h"
#include "Body.h"
#include <algorithm>
#include <cmath>
#include <iostream>
Particle::Particle(Vector2 position, Vector2 velocity, Vector2 acceleration, float mass, Color color, float delay): Body(position, velocity, acceleration, mass, color), startingVelocity{velocity}, delay{delay}, startingDelay{delay}, startingX{position.x}, startingY{position.y}{};
Particle::Particle(Vector2 position, float mass, Color color, float delay):  Body(position, mass, color), startingVelocity(Vector2{0,0}), delay{delay}, startingDelay{delay}, startingX{position.x}, startingY{position.y}{};

void Particle::Reset(){
  lifeSpan = 255;
  position = Vector2{startingX, startingY};
  velocity = Vector2{startingVelocity.x, startingVelocity.y};
  acceleration = Vector2{0,0};
  delay = startingDelay;
}
void Particle::Update(float dt){
  
  if(delay <= 0){

    Body::Update(dt);
    lifeSpan -= dt*100;

    if(lifeSpan <= 0){
      Reset();
    }
  }else{
    delay -= dt*100;
  }

}
void Particle::Draw(){
  if(delay <= 0){

    angle = atan2f(velocity.y, velocity.x);
    color.a = lifeSpan;
    DrawCircle(position.x, position.y, mass * 16, color);
  }
}

