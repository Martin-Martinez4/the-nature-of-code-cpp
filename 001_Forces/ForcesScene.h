#ifndef FORCES_FORCES_SCENE_H_
#define FORCES_FORCES_SCENE_H_

#include "Body.h"
#include "Liquid.h"
#include "Scene.h"
#include "raylib.h"
#include <vector>

class ForcesScene: public Scene{

public:
  ForcesScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;
  void DrawGUI();

private:
  std::string name = "Forces";
  std::vector<Body> movers = {};
  std::vector<Liquid> liquids = {};

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = true;

  Vector2 gravity = {0.0f, 0.1f};
  Vector2 wind = {0.1, 0};
  Vector2 clickForce = {2.f, 2.f};
};

#endif
