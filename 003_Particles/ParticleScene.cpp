
#include "ParticleScene.h"
#include "raylib.h"
#include <iostream>

ParticleScene::ParticleScene(SceneStack& sceneStack, int winWidth, int winHeight):Scene(sceneStack, winWidth, winHeight){
  Init();
};

void ParticleScene::Init() {
  //particles.push_back(Particle{Vector2{(float)(winWidth/2),0}, 1, PURPLE, 100});

}
void ParticleScene::Update(double dt) {
  if(!isPaused){
    pe.ApplyForce(gravity);
    pe.Update(dt);
  }
}
void ParticleScene::Draw() {

  BeginDrawing();
  /*
  for(int i = 0; i < particles.size(); ++i){
    particles[i].Draw();
  }
  */
  pe.Draw();
  DrawGUI();
  EndDrawing();


  ClearBackground(BLACK);
}
const std::string& ParticleScene::GetSceneName() const {
  return name;
}
const void ParticleScene::HandleInput() {}
void ParticleScene::DrawGUI() {}
