#ifndef AGENTS_PATH_AGENT_H_
#define AGENTS_PATH_AGENT_H_


#include "Body.h"
#include "Path.h"
#include "raylib.h"
class PathAgent: public Body{
public:
  PathAgent(Vector2 position = Vector2{0,0},  float mass = 10.f, Color color = RED);

  void Update(double dt);
  void Draw();

  void Follow(Path& path);


private:
  float maxSpeed = 8;
  float maxForce = 0.2;

  Vector2 GetNormalPoint(Vector2 future, Path& path);
  void Seek(Vector2 target);
};
#endif // !AGENTS_PATH_AGENT_H_
