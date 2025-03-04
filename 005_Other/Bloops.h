#ifndef OTHER_BLOOPS_H_
#define OTHER_BLOOPS_H_

#include "Scene.h"
#include "raylib.h"
#include "Number.h"
#include <cstdlib>
#include <vector>

// ===== Food =====
struct Food{
  Food(Vector2 position);
  Vector2 position;
  bool isAlive = true;
  void Update(double dt);

  float size = 16;
  
  void Draw();
};

// ===== Bloop DNA =====
struct BloopDNA{
  BloopDNA();
  BloopDNA(float mutationRate);
  BloopDNA::BloopDNA(float mutationRate, float geneValue);

  float mutationRate;
  float geneValue;

  BloopDNA CreateCopy();
  void Mutate();
};

// ===== Bloop =====
class Bloop{
public:
  Bloop(Vector2 position);
  Bloop(Vector2 position, BloopDNA dna);

  BloopDNA dna;

  Vector2 position;
  Vector2 velocity;

  float xOff = rand() % 1000;
  float yOff = rand() % 1000;

  float maxSpeed = 3.f;
  float radius;

  Color color = BLUE;
  
  void Update(double dt);
  void Draw();

  bool IsDead();

  void Eat();

  bool Reproduce();
  void Mutate();

private:

  float health = 50;
};


// ===== Scene =====
// The scene is the world
class BloopsScene: public Scene{

public:
  BloopsScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;

  void CleanUp();
  virtual const std::string& GetSceneName() const override;

private:
  std::string name = "Bloops";
  std::vector<Bloop> bloops = {Bloop(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}, BloopDNA{randomFloat(0.1, 1), randomFloat(0.1, 1)}), Bloop(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}, BloopDNA{randomFloat(0.1, 1), randomFloat(0.1, 1)}),Bloop(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}, BloopDNA{randomFloat(0.1, 1), randomFloat(0.1, 1)}),};
  std::vector<Food> food = {Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}), Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}), Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}), Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}), Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}), Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}), Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)}), Food(Vector2{randomFloat(0, winWidth), randomFloat(0, winHeight)})};


  bool isPaused = false;

  float CleanUpTime = 2;
  float TimeToCleanUp = CleanUpTime;



};


#endif
