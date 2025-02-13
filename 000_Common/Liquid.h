#ifndef COMMON_LIQUID_H_
#define COMMON_LIQUID_H_

#include "Body.h"
#include "raylib.h"
#include <cstdint>
class Liquid{
public:
  Liquid(float x, float y, float w, float h, float c = 0.1);
  void ApplyForce(Vector2 force);
  void Update(uint32_t dt);
  void Draw();

  bool ContainsMover(Body& body);
  Vector2  CalculateDrag(Body& body);

  Rectangle rectangle;

private:
  float x, y, w, h, c;
};

#endif
