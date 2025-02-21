#include "Agent.h"
#include "raylib.h"
#include <limits>
#include <cmath>
#include <iostream>
#include <raymath.h>

Agent::Agent(std::vector<Target>& targets, Vector2 position, float mass, Color color):Body(position, mass, color), targets{targets}{
  FindNextTarget();
  std::clog <<"Target Index: " << targetIndex << "\n";
  SetCourse();
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

  SetCourse();
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

void Agent::SetCourse(){
  // Apply Force here
  ApplyForce(Vector2Subtract(targets[targetIndex].position, position) * .001);
}