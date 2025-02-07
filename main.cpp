

#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include "FollowMouseScene.h"
#include "NormalDistributionScene.h"
#include "OptionsScene.h"
#include "PerlinNoiseScene.h"
#include "Scene.h"
#include "VelocityScene.h"
#include "raylib.h"
#include "Random.h"

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
    {"Velocity", "Follow the Mouse"}, 
    {
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new VelocityScene(sceneStack, winWidth, winHeight)));
      }, 
      [&sceneStack](){
        sceneStack.push(std::shared_ptr<Scene>(new FollowMouseScene(sceneStack, winWidth, winHeight)));
      }, 
    }
  ));
  
  auto chapterSelectScene = std::shared_ptr<Scene>(new OptionsScene(sceneStack, winWidth, winHeight, 
      {"Randomness", "Forces"}, 
      {
        [&sceneStack, randomnessSelectScene](){
          sceneStack.push(randomnessSelectScene);                                                              
        }, 
        [&sceneStack, forcesSelectScene](){

          sceneStack.push(forcesSelectScene);                                                              
        }, 
      }
    )
  );
  
  sceneStack.push(chapterSelectScene);

  SetTargetFPS(60);
  while(!WindowShouldClose()){

    //vas.Update(GetFrameTime());
    //vas.Draw();

    auto current = sceneStack.top();
    current->Update(GetFrameTime());
    current->Draw();
    current->HandleInput();
    
  }

  CloseWindow();

  return 0;
}


