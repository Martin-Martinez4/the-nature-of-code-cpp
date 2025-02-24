
#ifndef AGENTS_PATH_FOLLOWING_SCENE_H_
#define AGENTS_PATH_FOLLOWING_SCENE_H_


#include "Path.h"
#include "PathAgent.h"
#include "Scene.h"
#include <string>
class PathFollowingScene: public Scene{

public:
  PathFollowingScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;
  void DrawGUI();

private:
  std::string name = "Follow Path";
  
  Path path = Path{Vector2{0,0}, Vector2{(float)winWidth, (float)(2 * winHeight)/3}, 20};
  
  PathAgent agent = PathAgent(Vector2{(float)winWidth/2, 0}, 1, WHITE);
  
  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = false;
  //Vector2 gravity = {0.0f, 0.1f};

};

#endif

