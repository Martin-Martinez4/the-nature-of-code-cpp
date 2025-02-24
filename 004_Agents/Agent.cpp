#include "Agent.h"
#include "raylib.h"
#include "Number.h"
#include <limits>
#include <cmath>
#include <raymath.h>

Agent::Agent(std::vector<Target>& targets, Vector2 position, float mass, Color color):Body(position, mass, color), targets{targets}{
  FindNextTarget();
  //SetCourse();
};

void Agent::Update(double dt){
  if(targetIndex == -1){
    velocity *= 0;
    acceleration *= 0;
    return;
  }

  if(Vector2Length(Vector2Subtract(position, targets[targetIndex].position)) <= (radius + targets[targetIndex].radius)){
    targets[targetIndex].isAlive = false;
    velocity *= 0;
    acceleration *= 0;
    FindNextTarget();
    if(targetIndex == -1){
      return;
    }
  }

  /*
  Vector2 desired = setMagnitude(Vector2Subtract(targets[targetIndex].position, position), maxSpeed);
  Vector2 steer = Vector2Subtract(desired, velocity);

  // turn into a its own function
  if(steer.x > maxForce){
    steer.x = maxForce;
  }else if(steer.x < -maxForce){
    steer.x = -maxForce;
  }
   if(steer.y > maxForce){
    steer.y = maxForce;
  }else if(steer.y < -maxForce){
    steer.y = -maxForce;
  }

  ApplyForce(steer);
  */
  Seek(Vector2Subtract(targets[targetIndex].position, position));

  Body::Update(dt);
}

void Agent::Draw(){
  DrawCircle(position.x, position.y, 8, GREEN);
}

void Agent::FindNextTarget(){
  // seek shortest distance from current distance
  // use squared distance, exact answer does not matter

  float smallestDistanceSqr = std::numeric_limits<float>::max();
  targetIndex = -1;

  for(int i = 0; i < targets.size(); ++i){

    if(targets[i].isAlive){
      if((powf(position.x - targets[i].position.x, 2) + powf(position.y - targets[i].position.y, 2)) <= smallestDistanceSqr){
        targetIndex = i;
        smallestDistanceSqr = (powf(position.x - targets[i].position.x, 2) + powf(position.y - targets[i].position.y, 2));
      }
    }
  }
}

void Agent::Seek(Vector2 target){

  Vector2 desired = setMagnitude(target, maxSpeed);
  Vector2 steer = Vector2Subtract(desired, velocity);

  // turn into a its own function
  if(steer.x > maxForce){
    steer.x = maxForce;
  }else if(steer.x < -maxForce){
    steer.x = -maxForce;
  }
   if(steer.y > maxForce){
    steer.y = maxForce;
  }else if(steer.y < -maxForce){
    steer.y = -maxForce;
  }

  ApplyForce(steer);
}


