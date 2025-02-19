
#include "AgentsScene.h"
#include "raylib.h"
#include <iostream>

AgentsScene::AgentsScene(SceneStack& sceneStack, int winWidth, int winHeight):Scene(sceneStack, winWidth, winHeight){
  Init();
};

void AgentsScene::Init() {}
void AgentsScene::Update(double dt) {
  if(!isPaused){
   
  }
}
void AgentsScene::Draw() {

  BeginDrawing();

  for(unsigned int i = 0; i < targets.size(); ++i){
    targets[i].Draw();
  }
 
  DrawGUI();
  EndDrawing();


  ClearBackground(BLACK);
}
const std::string& AgentsScene::GetSceneName() const {
  return name;
}
const void AgentsScene::HandleInput() {}
void AgentsScene::DrawGUI() {}
