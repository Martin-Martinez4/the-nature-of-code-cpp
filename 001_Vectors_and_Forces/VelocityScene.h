
#ifndef VECTORS_VELOCITYSCENE
#define VECTORS_VELOCITYSCENE

#include "Scene.h"
#include "raylib.h"

class VelocityScene : public Scene{

public:
  VelocityScene(SceneStack& sceneStack, int winWidth, int winHeight, float bottomPadding = 10.0f, float xPadding = 10.f, float maxVelocity = 10.0f, Vector2 position = Vector2{0,0}, Vector2 velocity = Vector2{0,0}, Vector2 acceleration = Vector2{-0.01, 0.01});
  
  virtual void Init() override;
  virtual void Update(uint32_t dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  //virtual const void HandleInput() override;

  float bottomPadding;
  float xPadding;

  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;

  float maxVelocity;

private:
  std::string name = "Velocity and Acceleration";
};
#endif // !VECTORS_VELOCITYSCENE
