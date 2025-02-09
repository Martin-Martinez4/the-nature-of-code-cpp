
#ifndef COMMON_MOVER_H_
#define COMMON_MOVER_H_

#include "raylib.h"
#include <cstdint>
class Mover{
public:
  Mover(Vector2 position = Vector2{0,0}, Vector2 velocity = Vector2{0,0}, Vector2 acceleration = Vector2{0,0}, float mass = 10.f, Color color = RED);
  Mover(Vector2 position = Vector2{0,0},  float mass = 10.f, Color color = RED);
  
  void ApplyForce(Vector2 force);
  void Update(uint32_t dt);
  void Draw();

private:

  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;
  float mass;

  Color color;
};

#endif


