#ifndef VELOCITY_FOLLOW_MOUSE_SCENE_H_
#define VELOCITY_FOLLOW_MOUSE_SCENE_H_

#include "Scene.h"
#include "raylib.h"
class FollowMouseScene: public Scene{

public:
  FollowMouseScene(SceneStack& sceneStack, int winWidth, int winHeight, float maxVelocity = 10.0f);
  
  virtual void Init() override;
  virtual void Update(uint32_t dt) override;
  void DrawGUI();
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  //virtual const void HandleInput() override;

  Vector2 position;
  Vector2 velocity = Vector2{0,0};
  Vector2 acceleration = Vector2{0,0};
  Vector2 targetPosition = Vector2{0,0};

  float maxVelocity;

private:
  std::string name = "Follow the Mouse";
};


#endif // !VELOCITY_FOLLOW_MOUSE_SCENE_H_

