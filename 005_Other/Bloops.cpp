#include "Bloops.h"
#include "Random.h"
#include "raymath.h"
#include <iostream>

// ===== Food =====
Food::Food(Vector2 position): position{position}{}
  
void Food::Draw(){
    DrawRectangle(position.x, position.y, size, size, GREEN);
   
}

void Food::Update(double dt){}

// ===== BloopDNA =====
BloopDNA::BloopDNA():mutationRate{randomFloat(0,1)}, geneValue{randomFloat(0,1)}{};
BloopDNA::BloopDNA(float mutationRate):mutationRate{mutationRate}, geneValue{randomFloat(0,1)}{};
BloopDNA::BloopDNA(float mutationRate, float geneValue):mutationRate{mutationRate}, geneValue{geneValue}{};

BloopDNA BloopDNA::CreateCopy(){
  return BloopDNA(mutationRate, geneValue);
}

void BloopDNA::Mutate(){
  if(randomFloat(0,1) < mutationRate){
    geneValue = randomFloat(0.1, 1);
  }
};

// ===== Bloop =====
Bloop::Bloop(Vector2 position):position{position}, dna{BloopDNA()}{}
Bloop::Bloop(Vector2 position, BloopDNA dna):position{position}, dna{dna}, radius{mapFloatToRange(dna.geneValue, 0.1, 1, 8, 64)}, maxSpeed{mapFloatToRange(1/dna.geneValue, 1, 10, .5f, 10.f)}{}
  
void Bloop::Update(double dt){
  if(!IsDead()){

    health -= 0.05;
    float vx = mapFloatToRange(perlin(xOff), -1, 1, -maxSpeed, maxSpeed);
    float vy = mapFloatToRange(perlin(yOff), -1, 1, -maxSpeed, maxSpeed);
    xOff += .01f;
    yOff += .01f;
    velocity = Vector2{vx, vy};
    position = Vector2Add(position, velocity);
  }
}
void Bloop::Draw(){
  if(!IsDead()){

    DrawCircle(position.x, position.y, radius, color);
    DrawText(&std::to_string(health)[0], position.x, position.y, 4, WHITE);
  }
}

bool Bloop::IsDead(){
  return (health <= 0);
}
void Bloop::Eat(){
  health += 100;
}

bool Bloop::Reproduce(){
  return randomFloat(0,1) < 0.0005;
  
}
void Bloop::Mutate(){
  dna.Mutate();
  radius = mapFloatToRange(dna.geneValue, 0.1, 1, 8, 64); 
  maxSpeed = mapFloatToRange(1/dna.geneValue, 1, 10, .5f, 10.f);
}



// ===== Scene =====
BloopsScene::BloopsScene(SceneStack& sceneStack, int winWidth, int winHeight): Scene(sceneStack, winWidth, winHeight){}

void BloopsScene::Init(){}
void BloopsScene::Update(double dt){

  for(int i = 0; i < bloops.size(); ++i){
    if(!bloops[i].IsDead()){

      bloops[i].Update(dt);
      for(int j = 0; j < food.size(); ++j){
        // check collision with food
        if(food[j].isAlive){
          if(Vector2Length(Vector2Subtract(bloops[i].position, food[j].position)) <= (bloops[i].radius + food[j].size/2)){
            food[j].isAlive = false;
            bloops[i].Eat();
          }

        }
      }

      // keep them from going off screen
      float radius = bloops[i].radius;
      if(bloops[i].position.y > (winHeight - radius - 1)){
        bloops[i].position.y = winHeight - radius - 1;
      }
      if(bloops[i].position.y < radius){
        bloops[i].position.y = radius;
      }
      if(bloops[i].position.x > (winWidth - radius - 1)){
        bloops[i].position.x = winWidth - radius - 1;
      }
      if(bloops[i].position.x < radius){
        bloops[i].position.x = radius;
      }
    }
    
  }

  TimeToCleanUp -= dt;
  if(TimeToCleanUp <= 0){
    CleanUp();
    TimeToCleanUp = CleanUpTime;
  }

  int size = bloops.size();
  for(int i = 0; i < size; ++i){
    if(bloops[i].Reproduce()){
      Bloop b = Bloop{Vector2{bloops[i].position.x, bloops[i].position.y}, bloops[i].dna};
      b.Mutate();
      bloops.push_back(b);
    }
  }


}
void BloopsScene::Draw(){
  BeginDrawing();
  for(int i = 0; i < bloops.size(); ++i){
    bloops[i].Draw();
  }
  for(int i = 0; i < food.size(); ++i){
    food[i].Draw();
  }
  EndDrawing();
  ClearBackground(BLACK);
}

void BloopsScene::CleanUp(){
 // will not run every update; make it run on a timer or something
 std::clog << "Clean up: \n";
  auto toRemove = std::remove_if(bloops.begin(), bloops.end(), [](Bloop b){return b.IsDead();});
  for(auto itr = toRemove; itr != bloops.end(); ++itr){
    food.push_back(Food(Vector2{itr->position.x, itr->position.y}));
  }
  bloops.erase(toRemove, bloops.end());

  auto toRemoveFood = std::remove_if(food.begin(), food.end(), [](Food f){return !f.isAlive;});
  food.erase(toRemoveFood, food.end());
}

const std::string& BloopsScene::GetSceneName() const{
  return name;
}


