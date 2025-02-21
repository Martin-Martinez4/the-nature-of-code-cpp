
#ifndef AGENTS_AGENT_H_
#define AGENTS_AGENT_H_

#include "Body.h"
#include "Target.h"
#include "raylib.h"
#include <vector>

class Agent: public Body{
public:
  Agent(std::vector<Target>& targets, Vector2 position = Vector2{0,0},  float mass = 10.f, Color color = RED);

  void Update(double dt);
  void Draw();

  std::vector<Target>& targets;

  // the index of the current target
  // if it is -1 the agent should not move
  unsigned int targetIndex = -1;
private:

  void FindNextTarget();

  float maxSpeed = 8;
  float maxForce = 0.2; 
};

#endif // !AGENTS_AGENT_H_



