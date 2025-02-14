
#ifndef FORCES_VELOCITY_SCENE
#define FORCES_VELOCITY_SCENE

#include "Scene.h"
#include "raylib.h"

class VelocityScene : public Scene{

public:
  VelocityScene(SceneStack& sceneStack, int winWidth, int winHeight, float bottomPadding = 10.0f, float xPadding = 10.f, float maxVelocity = 10.0f, Vector2 position = Vector2{0,0}, Vector2 velocity = Vector2{0,0}, Vector2 acceleration = Vector2{-0.01, 0.01});
  
  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;
  void CleanUpAndExit();
  void DrawGUI();

  float bottomPadding;
  float xPadding;

  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;

  float maxVelocity;

private:
  std::string name = "Velocity and Acceleration";
  bool showDemoWindow = false;
};
#endif // !FORCES_VELOCITY_SCENE
