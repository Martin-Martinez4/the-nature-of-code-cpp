#ifndef AGENTS_AGENTS_SCENE_H_
#define AGENTS_AGENTS_SCENE_H_



#include "Scene.h"
#include "Agent.h"
#include "Target.h"
#include "raylib.h"
#include <string>
class AgentsScene: public Scene{

public:
  AgentsScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;
  void DrawGUI();

private:
  std::string name = "Agents";

  std::vector<Target> targets = {Target(Vector2{100, 100}, 1, GREEN), Target(Vector2{200, 150}, 2, BLUE)};
  Agent agent = Agent(targets, Vector2{0.f,0.f}, 1, WHITE);
  
  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = false;
  //Vector2 gravity = {0.0f, 0.1f};

};

#endif // !AGENTS_AGENTS_SCENE_H_

