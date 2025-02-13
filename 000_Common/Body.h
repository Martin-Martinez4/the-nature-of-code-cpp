
#ifndef COMMON_MOVER_H_
#define COMMON_MOVER_H_

#include "raylib.h"
#include <cstdint>
#include <vector>
class Body{
public:
  Body(Vector2 position = Vector2{0,0}, Vector2 velocity = Vector2{0,0}, Vector2 acceleration = Vector2{0,0}, float mass = 10.f, Color color = RED);
  Body(Vector2 position = Vector2{0,0},  float mass = 10.f, Color color = RED);
  
  void ApplyForce(Vector2 force);
  void Update(uint32_t dt);
  void Draw();

  Vector2 Attract(Body& body);

  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;
  
  float angle = 0.f;
  float anglularVelocity = 0.f;
  float angularAcceleration = 0.f;

  float mass = 1;
  float radius = mass * 16;
  float energyConservationRate = 0.75;

  Color color;

  std::vector<Body*> attractedBodies{};
};

#endif


