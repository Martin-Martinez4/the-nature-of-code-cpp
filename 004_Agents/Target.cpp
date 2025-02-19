#include "Target.h"
#include "raylib.h"

Target::Target(Vector2 position, float mass, Color color): Body(position, mass, color){}
void Target::Update(double dt){
  // does nothing for now
};
void Target::Draw(){
  if(isAlive){
    Body::Draw();
  }
};
