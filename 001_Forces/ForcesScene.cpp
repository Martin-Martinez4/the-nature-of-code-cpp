
#include "ForcesScene.h"
#include "Mover.h"
#include "Scene.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"
#include "imgui.h"
#include "Number.h"
#include <cmath>

ForcesScene::ForcesScene(SceneStack& sceneStack, int winWidth, int winHeight): Scene(sceneStack, winWidth, winHeight){};

void ForcesScene::Init() {}
void ForcesScene::Update(uint32_t dt) {
  if(!isPaused){

    for(int i = 0; i < movers.size(); ++i){

      movers[i].ApplyForce(Vector2{gravity.x * movers[i].mass, gravity.y * movers[i].mass});
    }

    for(int i = 0; i < movers.size(); ++i){
      movers[i].Update(dt);

      if(isContactingEdge(movers[i], winWidth, winHeight)){
        if(fabs(movers[i].velocity.x) > 0.1 || fabs(movers[i].velocity.y) > 0.1){  
          float c = 0.1f;
          Vector2 friction = setMagnitude(movers[i].velocity * -1, c);
          movers[i].ApplyForce(friction);
        }
      }
      bounceOnEdge(movers[i], winWidth, winHeight);
    }
  }
}
void ForcesScene::Draw() {

  BeginDrawing();
  

  for(int i = 0; i < movers.size(); ++i){
    movers[i].Draw();
  }

  DrawGUI();
  EndDrawing();


  ClearBackground(BLACK);
}
const std::string& ForcesScene::GetSceneName() const {
  return name;
}
//const void HandleInput() {}
void ForcesScene::DrawGUI(){
 
  rlImGuiBegin();
  if(ImGui::BeginMainMenuBar()){

    if(ImGui::BeginMenu("File")){
      if(ImGui::MenuItem("Quit")){
        sceneStack.pop();
        ImGui::End();

        // end ImGui Content
        rlImGuiEnd();
      }

      ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Scene")){
      
      if(isPaused){
        if(ImGui::MenuItem("Play")){
          isPaused = false;
        }
      }else{
        if(ImGui::MenuItem("Pause")){
          isPaused = true;
        }
      }
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }// show some windows

	if (ImGui::Begin("Objects")){
    
    if(ImGui::CollapsingHeader("Add Object")){

        ImGui::Columns(2);
        if(ImGui::InputFloat("X", &tempX)){
          tempX = simpleClamp(tempX, 0.f, float(winWidth));
        }

        ImGui::NextColumn();

        if(ImGui::InputFloat("Y", &tempY)){
          tempY = simpleClamp(tempY, 0.f, float(winHeight));
        }

      ImGui::Columns(1);

      if(ImGui::InputFloat("Mass", &tempMass)){
        tempMass = simpleClamp(tempMass, 1.f, float(100));
      }
      if(ImGui::Button("Add Mover")){
        movers.push_back(Mover(Vector2{tempX, tempY}, tempMass, BLUE));
      } 
    }
    
	}
	
  ImGui::End();

	// end ImGui Content
	rlImGuiEnd();
};
