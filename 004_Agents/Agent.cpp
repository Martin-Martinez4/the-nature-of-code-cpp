#include "Agent.h"

Agent::Agent(std::vector<Target>& targets, Vector2 position, float mass, Color color):Body(position, mass, color), targets{targets}{};

void Agent::Update(double dt){
  if(targetIndex == -1){
    return;
  }

  if(position.x == targets[targetIndex].position.x && position.y == targets[targetIndex].position.y){
    targets[targetIndex].isAlive = false;
    FindNextTarget();
    if(targetIndex == -1){
      return;
    }
  }

  SetCourse();
  Body::Update(dt);
}

void Agent::Draw(){

}

void Agent::FindNextTarget(){
  // seek shortest distance from current distance
}

void Agent::SetCourse(){
  // Apply Force here
}