
#include "PathFollowingScene.h"

PathFollowingScene::PathFollowingScene(SceneStack& sceneStack, int winWidth, int winHeight):Scene(sceneStack, winWidth, winHeight){
  Init();
};

void PathFollowingScene::Init() {}

void PathFollowingScene::Update(double dt) {
  if(!isPaused){
    agent.Follow(path);
    agent.Update(dt);
   
  }
}
void PathFollowingScene::Draw() {

  BeginDrawing();

  path.Draw();
  agent.Draw();

  DrawGUI();
  EndDrawing();


  ClearBackground(BLACK);
}
const std::string& PathFollowingScene::GetSceneName() const {
  return name;
}
const void PathFollowingScene::HandleInput() {}
void PathFollowingScene::DrawGUI() {}
