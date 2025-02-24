
#include "GameOfLife.h"
#include "Scene.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

GameOfLifeScene::GameOfLifeScene(SceneStack& sceneStack, int winWidth, int winHeight):Scene(sceneStack, winWidth, winHeight){
  Init();
};

void GameOfLifeScene::Init(){

  columns = winWidth/w;
  rows = winHeight/w;

  board = std::vector<std::vector<int>>(columns, std::vector<int>(rows, 0));
  
  for(int c = 0; c < columns; ++c){
    for(int r = 0; r < rows; ++r){
        board[c][r] = rand() % 2;
    }
  }
}
void GameOfLifeScene::Draw(){
  BeginDrawing();
  for(int c = 0; c < columns; ++c){
    for(int r = 0; r < rows; ++r){
      if(board[c][r] == 1){
        DrawRectangle(c * w, r * w, w, w, WHITE);
      }
    }
  }
  //DrawRectangle(winWidth/2, winHeight/2, w, w, WHITE);
  EndDrawing();
  ClearBackground(BLACK);
}
void GameOfLifeScene::Update(double dt){}
const std::string& GameOfLifeScene::GetSceneName() const {
  return name;
}
//void GameOfLifeScene::DrawGUI(){}
