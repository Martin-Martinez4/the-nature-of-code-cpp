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
    genes.push_back(Vector2{randomFloat(0, 1), randomFloat(0,1)});
    genes[i] *= randomFloat(0, maxForce);
  }
};

void DNA::Mutate(float mutationRate){
  for(int i = 0; i < length; ++i){
    if(randomFloat(0,1) > mutationRate){
      genes[i] = randomNormailzedVector();
    }
  }
}

// ===== Rocket =====
Rocket::Rocket(Vector2 target, DNA dna, int lifeSpan, Vector2 position, Vector2 velocity, Vector2 acceleration, float mass, Color color):Body(position, velocity, acceleration, mass, color), target{target}, lifeSpan{lifeSpan}, dna{dna}{};


void Rocket::Update(double dt){
  ApplyForce(dna.genes[geneIndex%lifeSpan]);
  Body::Update(dt);
  geneIndex++;
}
DNA Rocket::CrossOver(Rocket rocket){
  DNA dna  = DNA(lifeSpan);
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


// ===== Population =====
Population::Population(Vector2 target, float mutationRate, int length):target{target}, mutationRate{mutationRate}, length{length}{
  Init();
};
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
    population.push_back(Rocket(target, DNA(timeToLive), timeToLive));
   }
}

void Population::Update(double dt){
  for(int i = 0; i < length; ++i){
    population[i].Update(dt);
  }

  timeAlive += dt * 5;

  if(timeAlive > timeToLive){
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
    newPopulation.push_back(Rocket(target, child, timeToLive));
   }

   population = newPopulation;
}


// ===== Scene =====
SmartRocketScene::SmartRocketScene(SceneStack& sceneStack, int winWidth, int winHeight):Scene(sceneStack, winWidth, winHeight), population{Population(Vector2{(float)winWidth/2, 48}, 0.1, 5)}{};

void SmartRocketScene::Init(){}
void SmartRocketScene::Draw(){
  BeginDrawing();

  population.Draw();
   
  EndDrawing();
  ClearBackground(BLACK);
}
void SmartRocketScene::Update(double dt){
  population.Update(dt);
}
const std::string& SmartRocketScene::GetSceneName() const {
  return name;
}

