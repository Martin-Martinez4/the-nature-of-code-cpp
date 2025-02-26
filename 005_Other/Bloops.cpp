#include "Bloops.h"
#include "Random.h"
#include "raymath.h"

// ===== Food =====
Food::Food(Vector2 position): position{position}{}
  
void Food::Draw(){
  if(isAlive){
    DrawRectangle(position.x, position.y, size, size, GREEN);
   
  }
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
    geneValue = randomFloat(0,1);
  }
};

// ===== Bloop =====
Bloop::Bloop(Vector2 position):position{position}, dna{BloopDNA()}{}
Bloop::Bloop(Vector2 position, BloopDNA dna):position{position}, dna{dna}{}
  
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

void Bloop::Reproduce(){

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
      if(bloops[i].position.y > (winHeight - bloops[i].radius - 1)){
        bloops[i].position.y = winHeight - bloops[i].radius - 1;
      }
      if(bloops[i].position.y < bloops[i].radius){
        bloops[i].position.y = bloops[i].radius;
      }
      if(bloops[i].position.x > (winWidth - bloops[i].radius - 1)){
        bloops[i].position.x = winWidth - bloops[i].radius - 1;
      }
      if(bloops[i].position.x < bloops[i].radius){
        bloops[i].position.x = bloops[i].radius;
      }
    }
    
  }

  // will not run every update; make it run on a timer or something
  auto toRemove = std::remove_if(bloops.begin(), bloops.end(), [](Bloop b){return b.IsDead();});
  bloops.erase(toRemove, bloops.end());
  // for(int i = 0; i < food.size(); ++i){
  //   food[i].Update(dt);
  // }
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
const std::string& BloopsScene::GetSceneName() const{
  return name;
}
