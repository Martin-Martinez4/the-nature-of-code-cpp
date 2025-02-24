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

class Rocket: public Body{
public:
  Rocket(Vector2 target,  DNA dna, int lifeSpan, Vector2 position = Vector2{0,0}, Vector2 velocity= Vector2{0,0}, Vector2 acceleration= Vector2{0,0}, float mass = 1, Color color = RED);


  float fitness = 0;
  int lifeSpan;
  Vector2 target;
  DNA dna;

  void Update(double dt);
  DNA CrossOver(Rocket rocket);
  void CalculateFitness(){
    fitness = 1/Vector2Distance(position, target);
  }

private:
  int geneIndex = 0;


};

class Population{
public:
  Population(Vector2 target, float mutationRate, int length);
  int generations = 0;

  int timeToLive = 5;
  float timeAlive = 0;

  float mutationRate;
  int length;
  Vector2 target;

  void Update(double dt);
  void Draw();

  void Fitness();
  void Selection();
  void Reproduction();

private:

  void Init();

  std::vector<Rocket> population;
  Rocket WeightedSelection();

};

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

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = false;



};

#endif

