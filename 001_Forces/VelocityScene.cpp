
#include "VelocityScene.h"
#include "Scene.h"
#include "raymath.h"
#include "rlImGui.h"
#include "imgui.h"
#include <utility>
VelocityScene::VelocityScene(SceneStack& sceneStack, int winWidth, int winHeight, float bottomPadding, float xPadding, float maxVelocity, Vector2 position, Vector2 velocity, Vector2 acceleration):
  Scene(sceneStack, winWidth, winHeight), bottomPadding{bottomPadding}, xPadding{xPadding}, maxVelocity{maxVelocity}, position{std::move(position)}, velocity{std::move(velocity)}, acceleration{std::move(acceleration)}{};

void VelocityScene::Init(){}
void VelocityScene::Update(double dt){

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
    //velocity = Vector2ClampValue(Vector2Add(velocity, acceleration), -maxVelocity, maxVelocity);

    float x = velocity.x + acceleration.x;
    if(x > maxVelocity){
      x = maxVelocity;
    }else if(x < -maxVelocity){
      x = -maxVelocity;
    }

    float y = velocity.y + acceleration.y;
    if(y > maxVelocity){
      y = maxVelocity;
    }else if(y < -maxVelocity){
      y = -maxVelocity;
    }

    velocity = Vector2{x, y};
}
void DoMainMenu(){
  
}
void VelocityScene::DrawGUI(){
  rlImGuiBegin();
  if(ImGui::BeginMainMenuBar()){
    if(ImGui::BeginMenu("File")){
      if(ImGui::MenuItem("Quit")){

      }

      ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Window")){
      if(ImGui::MenuItem("Demo Window", nullptr, showDemoWindow)){
        showDemoWindow = !showDemoWindow;
      }
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }// show some windows
	
		if (showDemoWindow){

    }
			ImGui::ShowDemoWindow(&showDemoWindow);

		if (ImGui::Begin("Test Window"))
		{
      if(ImGui::SliderFloat("Velocity x", &velocity.x, -maxVelocity, maxVelocity)){}
      if(ImGui::SliderFloat("Velocity y", &velocity.y, -maxVelocity, maxVelocity)){}
    
      if(ImGui::SliderFloat("Acceleration x", &acceleration.x, -0.05, 0.05)){}
      if(ImGui::SliderFloat("Acceleration y", &acceleration.y, -.05, .05)){}
		}
		ImGui::End();

		// end ImGui Content
		rlImGuiEnd();
}
void VelocityScene::Draw(){

    BeginDrawing();
    
    DrawGUI();
  
    DrawCircle(position.x, position.y, 10.f, RED);

    EndDrawing();

    ClearBackground(BLACK);
}

void VelocityScene::CleanUpAndExit(){

  sceneStack.pop();

}

const void VelocityScene::HandleInput(){

  if(IsKeyPressed(KEY_BACKSPACE)){
    CleanUpAndExit();
  }
}

const std::string& VelocityScene::GetSceneName() const{
  return name;
}

