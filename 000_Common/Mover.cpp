
#include "Mover.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdint>

Mover::Mover(Vector2 position, Vector2 velocity, Vector2 acceleration, float mass, Color color):position{position}, velocity{velocity}, acceleration{acceleration}, mass{mass}, color{color}{};
Mover::Mover(Vector2 position, float mass, Color color):Mover(position, Vector2{0,0}, Vector2{0,0}, mass, color){};
  
void Mover::ApplyForce(Vector2 force){
  
  acceleration = Vector2Add(acceleration, force / mass);
}

void Mover::Update(uint32_t dt){
  velocity += acceleration;
  position += velocity;
  acceleration *= 0;
}

void Mover::Draw(){
  //BeginDrawing();
  DrawCircle(position.x, position.y, mass * 16, RED);
  //EndDrawing();
}
