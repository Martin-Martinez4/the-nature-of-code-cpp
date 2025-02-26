#ifndef OTHER_BLOOPS_H_
#define OTHER_BLOOPS_H_

#include "Scene.h"
#include "raylib.h"
#include <cstdlib>
// ===== Food =====
struct Food{
  Food(Vector2 position);
  Vector2 position;
  bool alive = true;
  
  void Draw();
};


// ===== Bloop =====
class Bloop{
public:
  Bloop(Vector2 position);

  Vector2 position;
  float xOff = rand() % 1000;
  float yOff = rand() % 1000;

  float maxSpeed = 5.f;
  float radius = 8.f;
  
  void Update(double dt);
  void Draw();

  bool IsDead();
  // Eat will just increase HP; world should handle changing the Food's state
  void Eat();

private:

  float health = 100;
};


// ===== Scene =====
// The scene is the world
class BloopsScene: public Scene{

public:
  BloopsScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;


 

private:
  std::string name = "Bloops";



  bool isPaused = false;



};


#endif
