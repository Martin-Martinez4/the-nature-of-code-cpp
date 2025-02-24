#ifndef OTHER_GAME_OF_LIFE_H_
#define OTHER_GAME_OF_LIFE_H_


#include "Scene.h"
#include <string>
#include <vector>
class GameOfLifeScene: public Scene{

public:
  GameOfLifeScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  //virtual const void HandleInput() override;
  //void DrawGUI();

private:
  std::string name = "Game Of Life";

  // similar to a double buffer set up
  std::vector<std::vector<int>> board0;
  std::vector<std::vector<int>> board1;

   std::vector<std::vector<int>>& currentBoard = board0;
   std::vector<std::vector<int>>& nextBoard = board1;

  int w = 8;
  int columns;
  int rows;

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = false;

  int NeighborSum(int c, int r);

  int generation = 0;

};

#endif

