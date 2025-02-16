

#include <cmath>
#include <iostream>
#include <memory>
#include "003_Particles/ParticleScene.h"
#include "FollowMouseScene.h"
#include "ForcesScene.h"
#include "NormalDistributionScene.h"
#include "OptionsScene.h"
#include "OscillationScene.h"
#include "PerlinNoiseScene.h"
#include "Scene.h"
#include "VelocityScene.h"
#include "raylib.h"
#include "Random.h"
#include "imgui.h"
#include "rlImGui.h"

int main(){

  SceneStack sceneStack;

  const int winWidth{920};
  const int winHeight{640};
  InitWindow(winWidth, winHeight, "Randomness");

  int xPadding = winWidth/20;

  auto nds = NormalDistributionScene{sceneStack, winWidth, winHeight, 10.f, 10.f};
  auto pns = PerlinNoiseScene(sceneStack, winWidth, winHeight);
  auto vas = VelocityScene(sceneStack, winWidth, winHeight);
  
  // todo: look for a better way to do this, it looks a bit messy
  auto randomnessSelectScene = std::shared_ptr<Scene>(new OptionsScene(sceneStack, winWidth, winHeight, 
    {"Normal Distribution", "Perlin Noise"}, 
    {
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new NormalDistributionScene{sceneStack, winWidth, winHeight, 10.f, 10.f}));
      }, 
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new PerlinNoiseScene(sceneStack, winWidth, winHeight)));
      },
    }
  ));

  auto forcesSelectScene = std::shared_ptr<Scene>(new OptionsScene(sceneStack, winWidth, winHeight, 
    {"Velocity", "Follow the Mouse", "Forces", "Oscillation"}, 
    {
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new VelocityScene(sceneStack, winWidth, winHeight)));
      }, 
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new FollowMouseScene(sceneStack, winWidth, winHeight)));
      }, 
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new ForcesScene(sceneStack, winWidth, winHeight)));
      }, 
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new OscillationScene(sceneStack, winWidth, winHeight)));
      }, 
    }
  ));
  
  auto particleSelectScene = std::shared_ptr<Scene>(new ParticleScene(sceneStack, winWidth, winHeight));
  
  auto chapterSelectScene = std::shared_ptr<Scene>(new OptionsScene(sceneStack, winWidth, winHeight, 
      {"Randomness", "Forces", "Particles"}, 
      {
        [&sceneStack, randomnessSelectScene](){
          sceneStack.push(randomnessSelectScene);                                                              
        }, 
        [&sceneStack, forcesSelectScene](){

          sceneStack.push(forcesSelectScene);                                                              
        },  
        [&sceneStack, particleSelectScene](){

          sceneStack.push(particleSelectScene);                                                              
        }, 
      }
    )
  );
  
  sceneStack.push(chapterSelectScene);

  SetTargetFPS(60);

  rlImGuiSetup(true);
  while(!WindowShouldClose()){
    auto current = sceneStack.top();
    current->Draw();
    current->Update(GetFrameTime());
    current->HandleInput();

    /*
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
    */
  }
  rlImGuiShutdown();
  CloseWindow();

  return 0;
}


