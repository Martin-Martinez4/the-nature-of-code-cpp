
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

  board0 = std::vector<std::vector<int>>(columns, std::vector<int>(rows, 0));
  board1 = std::vector<std::vector<int>>(columns, std::vector<int>(rows, 0));
  
  for(int c = 0; c < columns; ++c){
    for(int r = 0; r < rows; ++r){
        board0[c][r] = rand() % 2;
    }
  }

  currentBoard = board0;
  nextBoard = board1;
}
void GameOfLifeScene::Draw(){
  BeginDrawing();
    for(int c = 0; c < columns; ++c){
      for(int r = 0; r < rows; ++r){
        if(currentBoard[c][r] == 1){
          DrawRectangle(c * w, r * w, w, w, WHITE);
        }
      }
    }
  
  //DrawRectangle(winWidth/2, winHeight/2, w, w, WHITE);
  EndDrawing();
  ClearBackground(BLACK);
}
void GameOfLifeScene::Update(double dt){

  for(int c = 0; c < columns; ++c){
    for(int r = 0; r < rows; ++r){
      int neighborsSum = NeighborSum(c, r);
      int currentVal = currentBoard[c][r];


      if(currentVal == 1 && neighborsSum < 2){
        nextBoard[c][r] = 0;
      }else if(currentVal == 1 && neighborsSum > 3){
        nextBoard[c][r] = 0;
      }else if(currentVal == 0 && neighborsSum == 3){
        nextBoard[c][r] = 1;
      }else{
        nextBoard[c][r] = currentVal;
      }
    }
  }

  if(currentBoard == board0){
    // update board1
    currentBoard = board1;
    nextBoard = board0;
  }else if(currentBoard == board1){
    // update board 0
    currentBoard = board0;
    nextBoard = board1;
  }
}
const std::string& GameOfLifeScene::GetSceneName() const {
  return name;
}
//void GameOfLifeScene::DrawGUI(){}

int GameOfLifeScene::NeighborSum(int c, int r){
  int neighborSum = 0;
  for(int k = -1; k <= 1; ++k){
    for(int l = -1; l <= 1; ++l){
      int newCol = c + k;
      int newRow = r + l;
      if(newCol < 0 || newCol >= columns || newRow < 0 || newRow >= rows){
        continue;
      }
      neighborSum += currentBoard[newCol][newRow];
    }
  }

  return neighborSum -= currentBoard[c][r];
}

