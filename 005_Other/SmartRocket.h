#ifndef OTHER_SMART_ROCKET_H_
#define OTHER_SMART_ROCKET_H_


#include "Scene.h"
#include "Body.h"
#include "raymath.h"
#include <string>
#include <vector>

class DNA {
public:
  DNA(int length);
  void Init();

  int length;

  std::vector<Vector2> genes;
  void Mutate(float mutationRate);

private:
  float maxForce = 0.1;
};

// ===== Rocket =====
class Rocket: public Body{
public:
  Rocket(Vector2 target,  DNA dna, int lifeSpan, Vector2 position = Vector2{0,0}, Vector2 velocity= Vector2{0,0}, Vector2 acceleration= Vector2{0,0}, float mass = 1, Color color = RED);

  float fitness = 0;
  int lifeSpan;
  bool hitObstacle = false;
  bool hitTarget = false;
  Vector2 target;
  DNA dna;


  void Update(double dt);
  DNA CrossOver(Rocket rocket);
  void CalculateFitness();
private:
  int geneIndex = 0;


};

// ===== Obstacle =====
class Obstacle{
public:
  Obstacle(Vector2 position, int width, int height, Color color);
  Vector2 position;
  int width;
  int height;
  Color color;

  void Draw();
  bool Contains(Vector2 position);

private:
};


class Population{
public:
  Population(Vector2 target, float mutationRate, int length);
  int generations = 0;

  int timeToLive = 100;
  float timeAlive = 0;

  float mutationRate;
  int length;
  Vector2 target;

  void CheckObstacleCollisions(std::vector<Obstacle>& obstacles);

  void Update(double dt);
  void Draw();

  void Fitness();
  void Selection();
  void Reproduction();
  void Init();

private:


  std::vector<Rocket> population;
  Rocket WeightedSelection();

};


// ===== Scene =====
class SmartRocketScene: public Scene{

public:
  SmartRocketScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;


 

private:
  std::string name = "Smart Rocket";

  Population population;
  std::vector<Obstacle> obstacles{Obstacle(Vector2{100, 550}, 60, 20, GREEN)};

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = false;



};

#endif

