
#include "OscillationScene.h"
#include "Scene.h"
#include "raylib.h"
#include "raymath.h"
#include "rlImGui.h"
#include "imgui.h"
#include "Number.h"
#include <cmath>
#include <iostream>

// ===== Oscillator =====

Oscillator::Oscillator(int winWidth, int winHeight):winWidth{winWidth}, winHeight{winHeight}{
  angle = Vector2{0,0};
  angularVelocity = Vector2{randomFloat(-0.1, 0.1), randomFloat(-0.1, 0.1)};
  amplitude = Vector2{randomFloat(10, winWidth/2), randomFloat(10, winHeight/2)};
};
void Oscillator::Update(double dt){
  angle = Vector2Add(angle, angularVelocity);
}
void Oscillator::Draw(){
  float x = sinf(angle.x) * amplitude.x;
  float y = sinf(angle.y) * amplitude.y;
  
  DrawLine(winWidth/2, winHeight/2, x + winWidth/2, y + winHeight/2, WHITE);
  DrawCircle(x + winWidth/2, y + winHeight/2, 32, RED);
}

// ===== Spring =====

Bob::Bob(Vector2 position,  float mass, Color color):Body(position, mass, color){};

Spring::Spring(float x, float y, int restLength):x{x}, y{y}, restLength{restLength}, anchor{Vector2{x,y}}{}
Vector2 Spring::Connnect(Bob& bob){
  Vector2 force = Vector2Subtract(bob.position, anchor);

  float currentLength = Vector2Length(force);
  float stretch = currentLength - restLength;

  force = setMagnitude(force, -1 * k * stretch);

  //ConstrainLength(force, 1, 2);
  float min = 0.001;
  float max = 640;
/*
  Vector2 dir = Vector2Subtract(anchor, bob.position);
  float d = Vector2Length(dir);

  if(d < min){
    dir = setMagnitude(dir, min);
    bob.position = Vector2Add(anchor, dir);
    bob.velocity *= 0;
  }else if(d > max){
    dir = setMagnitude(dir, max);
    bob.position = Vector2Add(anchor, dir);
    bob.velocity *= 0;
  }
  */
  return force;

}

void Spring::ConstrainLength(Vector2& force, float min, float max){
  float currentLength = Vector2Length(force);

  if(currentLength < min){
    force = setMagnitude(force, min);
  }else if(currentLength > max){
    force = setMagnitude(force, max);
  }
}

void Spring::Draw(){
  DrawCircle(anchor.x, anchor.y, 16, BLUE);
}

// ===== Pendulum =====

Pendulum::Pendulum(float x, float y, float r):pivot{Vector2{x,y}}, r{r}{
  bob = Vector2{x, 500};
}

void Pendulum::Update(double dt){
  float gravity = 0.1;
  angularAcceleration = ((-1*gravity / r) * sinf(angle))/dt;
  angularVelocity += angularAcceleration;
  angle += angularVelocity;
  angularVelocity *= damping;
}
void Pendulum::Draw(){
  bob.x = r * sinf(angle);
  bob.y = r * cosf(angle);
  bob += pivot;
  DrawLine(pivot.x, pivot.y, bob.x, bob.y, WHITE);
  DrawCircle(bob.x, bob.y, ballr * 2, BLUE);
}


// ===== Scene =====
OscillationScene::OscillationScene(SceneStack& sceneStack, int winWidth, int winHeight): Scene(sceneStack, winWidth, winHeight){
  Init();
};

void OscillationScene::Init() {
  for(int i = 0; i < 1; ++i){

    oscillators.push_back(Oscillator(winWidth, winHeight));
  }


}
void OscillationScene::Update(double dt) {
  if(!isPaused){
    pendulum.Update(dt); 
    for(int i = 0; i < oscillators.size(); ++i){
      oscillators[i].Update(dt);
    }
  }
}
void OscillationScene::Draw() {

  BeginDrawing();

  for(int i = 0; i < oscillators.size(); ++i){
    oscillators[i].Draw();
  }

  pendulum.Draw();

  DrawGUI();
  EndDrawing();


  ClearBackground(BLACK);
}
const std::string& OscillationScene::GetSceneName() const {
  return name;
}
//const void HandleInput() {}
void OscillationScene::DrawGUI(){
 
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
      /*
      if(ImGui::Button("Add Mover")){
        movers.push_back(Body(Vector2{tempX, tempY}, tempMass, BLUE));
      }
      */
    }
    
	}
	
  ImGui::End();

	// end ImGui Content
	rlImGuiEnd();
};

const void OscillationScene::HandleInput(){
  if(IsKeyPressed(KEY_A)){
    std::clog << "A Pressed\n";
  }
}
