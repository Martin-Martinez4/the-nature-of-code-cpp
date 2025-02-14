
#include "OptionsScene.h"
#include "Scene.h"
#include "raylib.h"
#include <cassert>
#include <iostream>
#include <string>
#include <utility>

OptionsScene::OptionsScene(SceneStack& sceneStack, int winWidth, int winHeight,std::vector<std::string> options, std::vector<std::function<void()>> actions): Scene(sceneStack, winWidth, winHeight), options{std::move(options)}, actions{std::move(actions)}{

  if(options.size() != actions.size()){
    std::clog << "OptionsScene: size of options and actions must be the same";
    assert(options.size() == actions.size());
  }
};

void OptionsScene::Init() {}
void OptionsScene::Update(double dt) {}
void OptionsScene::Draw(){
  ClearBackground(BLACK);
  BeginDrawing();
  
  int y = 10;
  int buttonHeight = 40;
  int halfWidth = winWidth/2;

  y = winHeight/2 - (options.size()-1 * 10) - (options.size() * buttonHeight);

  for(int i = 0; i < options.size(); ++i){

    Vector2 stringSize = MeasureTextEx(GetFontDefault(), &options[i][0], 24, 2);
    

    if(i == optionIndex){
      DrawRectangle(halfWidth - stringSize.x / 2 - 20, y, stringSize.x + 40, 40, WHITE);
    }else{

      DrawRectangle(halfWidth - stringSize.x / 2 - 20, y, stringSize.x + 40, 40, GRAY);
    }

    int stringPosV = y + int(buttonHeight/2) - stringSize.y/2;
    
    DrawText(&options[i][0], halfWidth - stringSize.x/2, stringPosV, 24, RED);
    
    y += buttonHeight + 10;
  }

  EndDrawing();


}
const std::string& OptionsScene::GetSceneName() const {
  return name;
}
const void OptionsScene::HandleInput() {
  if(IsKeyPressed(KEY_ENTER)){
    actions[optionIndex]();
  }
  if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
    if(optionIndex < actions.size() - 1){
      optionIndex++;
    }
  }
  if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
    if(optionIndex > 0){
      optionIndex--;
    } 
  }

  if(IsKeyPressed(KEY_BACKSPACE) && sceneStack.size() > 1){
    sceneStack.pop();
  }
}


