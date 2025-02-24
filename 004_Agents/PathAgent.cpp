
#include "PathAgent.h"
#include "Body.h"
#include "Number.h"
#include "raymath.h"

PathAgent::PathAgent(Vector2 position,  float mass, Color color):Body(position, mass, color){};

void PathAgent::Update(double dt){
  Body::Update(dt);
};
void PathAgent::Draw(){
  Body::Draw();
};

void PathAgent::Follow(Path& path){

  Vector2 future = velocity;
  future = setMagnitude(future, 25);
  future = Vector2Add(future, position);

  Vector2 normalPoint = GetNormalPoint(future, path);
  Vector2 b = Vector2Subtract(path.end, path.start);
  b = setMagnitude(b, 25);
  Vector2 target = Vector2Add(normalPoint, b);

  float distance = Vector2Distance(normalPoint, future);
  if(distance > path.radius){
    Seek(target);
  }

};

Vector2 PathAgent::GetNormalPoint(Vector2 future, Path& path){
  Vector2 vectorA = Vector2Subtract(position, path.start);

  Vector2 vectorB = Vector2Subtract(path.end, path.start);
  vectorB = Vector2Normalize(vectorB);
  vectorB *= Vector2DotProduct(vectorA, vectorB);

  return Vector2Add(path.start, vectorB);
};

void PathAgent::Seek(Vector2 target){

  Vector2 desired = setMagnitude(target, maxSpeed);
  Vector2 steer = Vector2Subtract(desired, velocity);

  // turn into a its own function
  if(steer.x > maxForce){
    steer.x = maxForce;
  }else if(steer.x < -maxForce){
    steer.x = -maxForce;
  }
   if(steer.y > maxForce){
    steer.y = maxForce;
  }else if(steer.y < -maxForce){
    steer.y = -maxForce;
  }

  ApplyForce(steer);
}
