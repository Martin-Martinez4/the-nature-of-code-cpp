
#include "FollowMouseScene.h"
#include "Scene.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"
#include "imgui.h"
FollowMouseScene::FollowMouseScene(SceneStack& sceneStack, int winWidth, int winHeight, float maxVelocity): Scene(sceneStack, winWidth, winHeight), maxVelocity{maxVelocity}{
  position = Vector2{winWidth/2.f, winHeight/2.f};
};

void FollowMouseScene::Init(){}
void FollowMouseScene::Update(double dt){
  targetPosition = GetMousePosition();
  Vector2 direction = Vector2Subtract(targetPosition, position);
  direction *= 0.2;
  acceleration = direction;

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

void FollowMouseScene::DrawGUI(){

    rlImGuiBegin();
    bool open = true;
    ImGui::ShowDemoWindow(&open);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    DrawFPS(190, 300);
    rlImGuiEnd();
}
void FollowMouseScene::Draw(){

    BeginDrawing();

    DrawGUI();
  
    DrawCircle(position.x, position.y, 10.f, RED);

    EndDrawing();

    ClearBackground(BLACK);
  }
const std::string& FollowMouseScene::GetSceneName() const{
  return name;
}
