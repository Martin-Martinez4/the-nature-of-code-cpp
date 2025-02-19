#ifndef AGENTS_TARGET_H_
#define AGENTS_TARGET_H_

#include "Body.h"
#include "raylib.h"

class Target: public Body{
public:

  Target(Vector2 position, float mass = 1.0f, Color color = RED);

  void Update(double dt);
  void Draw();

  bool isAlive = true;
private:
};

#endif
