#ifndef FORCES_FORCES_SCENE_H_
#define FORCES_FORCES_SCENE_H_

#include "Mover.h"
#include "Scene.h"
#include "raylib.h"
#include <vector>

class ForcesScene: public Scene{

public:
  ForcesScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(uint32_t dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  //virtual const void HandleInput() override;
  void DrawGUI();

private:
  std::string name = "Forces";
  std::vector<Mover> movers = {};

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = true;

  Vector2 gravity = {0, 0.1};
  Vector2 wind = {0.1, 0};
};

#endif
