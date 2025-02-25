#include "SmartRocket.h"
#include "Scene.h"
#include "raylib.h"
#include "Number.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ===== DNA =====
DNA::DNA(int length):length{length}{
  Init();
};
void DNA::Init(){

  for(int i = 0; i < length; ++i){
    genes.push_back(randomNormailzedVector());
    genes[i] *= randomFloat(0, maxForce);
  }
};

void DNA::Mutate(float mutationRate){
  for(int i = 0; i < length; ++i){
    if(randomFloat(0,1) < mutationRate){
      genes[i] = randomNormailzedVector();
    }
  }
}

// ===== Rocket =====
Rocket::Rocket(Vector2 target, DNA dna, int lifeSpan, Vector2 position, Vector2 velocity, Vector2 acceleration, float mass, Color color):Body(position, velocity, acceleration, mass, color), target{target}, lifeSpan{lifeSpan}, dna{dna}{};


void Rocket::Update(double dt){
  if(!hitObstacle && !hitTarget){

    ApplyForce(dna.genes[geneIndex]);
    Body::Update(dt);
    geneIndex++;

    // check if target was hit
  }
}

void Rocket::CalculateFitness(){
  float distance = 1/Vector2Distance(position, target);
  fitness = powf(distance, 2);

  if(hitObstacle){
    fitness *= 0.1;
  }

  if(hitTarget){
    fitness *= 2;
  }
}
DNA Rocket::CrossOver(Rocket rocket){
  DNA dna = DNA(lifeSpan);
  int midpoint = rand() % lifeSpan;

  for(int i = 0; i < lifeSpan; ++i){
    if(i < midpoint){
      dna.genes[i] = this->dna.genes[i];
    }else{

      dna.genes[i] = rocket.dna.genes[i];
    }
  }

  return dna;
}

// ===== Obstacle =====
Obstacle::Obstacle(Vector2 position, int width, int height, Color color):position{position}, width{width}, height{height}, color{color}{};

void Obstacle::Draw(){
  DrawRectangle(position.x, position.y, width, height, color);
}
bool Obstacle::Contains(Vector2 position){
   return (
      position.x > this->position.x &&
      position.x < this->position.x + width &&
      position.y > this->position.y &&
      position.y < this->position.y + height
    );
}

// ===== Population =====
Population::Population(Vector2 target, float mutationRate, int length):target{target}, mutationRate{mutationRate}, length{length}{};
Rocket Population::WeightedSelection(){
  int index = 0;
  float start = randomFloat(0, 1);
  while(start > 0){
    start -= population[index].fitness;
    index++;
  }
  index--;
  return population[index];
}
void Population::Init(){
   for(int i = 0; i < length; ++i){
    population.push_back(Rocket(target, DNA(timeToLive), timeToLive, Vector2{100, 600}));
   }
}

void Population::CheckObstacleCollisions(std::vector<Obstacle>& obstacles){
  for(int i = 0; i < population.size(); ++i){

    if(!population[i].hitObstacle && !population[i].hitTarget){

      for(int j = 0; j < obstacles.size(); ++j){
        if(obstacles[j].Contains(population[i].position)){
          population[i].hitObstacle = true;
        }
      }
    }
  }
}


void Population::Update(double dt){
  for(int i = 0; i < length; ++i){
    population[i].Update(dt);
  }

  timeAlive += 1;

  if(timeAlive >= timeToLive){
    Fitness();
    Selection();
    Reproduction();
    timeAlive = 0;
  }
}
void Population::Draw(){
  DrawCircle(target.x, target.y, 3, BLUE);
  for(int i = 0; i < length; ++i){
    population[i].Draw();
  }
}

void Population::Fitness(){
  for(int i = 0; i < population.size(); ++i){
    population[i].CalculateFitness();
  }
}

void Population::Selection(){
  float totalFitness = 0;
  for(int i = 0; i < population.size(); ++i){
    totalFitness += population[i].fitness;
  }
  for(int i = 0; i < population.size(); ++i){
    population[i].fitness /= totalFitness;
  }

}

void Population::Reproduction(){
  std::vector<Rocket> newPopulation;
  for(int i = 0; i < population.size(); ++i){
    Rocket parentA = WeightedSelection();
    Rocket parentB = WeightedSelection();
    DNA child = parentA.CrossOver(parentB);
    child.Mutate(mutationRate);
    newPopulation.push_back(Rocket(target, child, timeToLive, Vector2{100, 600}));
  }

   population = newPopulation;
}


// ===== Scene =====
SmartRocketScene::SmartRocketScene(SceneStack& sceneStack, int winWidth, int winHeight):Scene(sceneStack, winWidth, winHeight), population{Population(Vector2{320, 220}, 0.001, 10)}{};

void SmartRocketScene::Init(){
  population.Init();
}
void SmartRocketScene::Draw(){
  BeginDrawing();

  population.Draw();
  for(int i = 0; i < obstacles.size(); ++i){
    obstacles[i].Draw();
  }
   
  EndDrawing();
  ClearBackground(BLACK);
}
void SmartRocketScene::Update(double dt){
  population.Update(dt);
  // check if any population hit any obstacle; if so change the hit obstacle to true
  population.CheckObstacleCollisions(obstacles);
}
const std::string& SmartRocketScene::GetSceneName() const {
  return name;
}

