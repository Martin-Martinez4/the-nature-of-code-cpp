
#include "AgentsScene.h"
#include "Number.h"
#include "Random.h"
#include "raylib.h"
#include <iostream>

AgentsScene::AgentsScene(SceneStack& sceneStack, int winWidth, int winHeight):Scene(sceneStack, winWidth, winHeight){
  Init();
};

void AgentsScene::Init() {
  for(int i = 0; i < 30; ++i){
    targets.push_back(Target(Vector2{randomFloat(16, winWidth-16), randomFloat(16, winHeight-16)}, 1, randomColor()));
  }
}
void AgentsScene::Update(double dt) {
  if(!isPaused){
    agent.Update(dt);
   
  }
}
void AgentsScene::Draw() {

  BeginDrawing();

  for(unsigned int i = 0; i < targets.size(); ++i){
    targets[i].Draw();
  }

  agent.Draw();
 
  DrawGUI();
  EndDrawing();


  ClearBackground(BLACK);
}
const std::string& AgentsScene::GetSceneName() const {
  return name;
}
const void AgentsScene::HandleInput() {}
void AgentsScene::DrawGUI() {}
