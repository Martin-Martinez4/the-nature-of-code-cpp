
#ifndef AGENTS_PATH_H_
#define AGENTS_PATH_H_

#include "raylib.h"
class Path {
public:
  Path(Vector2 start, Vector2 end, float radius);

  float radius;
  Vector2 start;
  Vector2 end;

  void Draw();
};

#endif



