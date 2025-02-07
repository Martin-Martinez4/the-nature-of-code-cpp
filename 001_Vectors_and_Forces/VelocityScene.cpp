
#include "VelocityScene.h"
#include "Scene.h"
#include "raymath.h"
#include <utility>
VelocityScene::VelocityScene(SceneStack& sceneStack, int winWidth, int winHeight, float bottomPadding, float xPadding, float maxVelocity, Vector2 position, Vector2 velocity, Vector2 acceleration):
  Scene(sceneStack, winWidth, winHeight), bottomPadding{bottomPadding}, xPadding{xPadding}, maxVelocity{maxVelocity}, position{std::move(position)}, velocity{std::move(velocity)}, acceleration{std::move(acceleration)}{};

void VelocityScene::Init(){}
void VelocityScene::Update(uint32_t dt){

  position = Vector2Add(position, Vector2AddValue(velocity, dt));
    if(position.x > winWidth){
      position.x = 0;
    }else if(position.x < 0){
      position.x = winWidth;
    }

    if(position.y > winHeight){
      position.y = 0;
    }else if(position.y < 0){
      position.y = winHeight;
    }
    velocity = Vector2ClampValue(Vector2Add(velocity, acceleration), -maxVelocity, maxVelocity);
}
void VelocityScene::Draw(){

    BeginDrawing();
  
    DrawCircle(position.x, position.y, 10.f, RED);

    EndDrawing();

    ClearBackground(BLACK);
}
const std::string& VelocityScene::GetSceneName() const{
  return name;
}
//const void VelocityScene::HandleInput(){}
