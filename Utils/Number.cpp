#include "Number.h"
#include "raymath.h"
#include <cstdlib>
#include <ctime>

void bounceOnEdge(Body& mover, int width, int height){
  if(mover.position.x >= width - mover.radius){
    mover.position.x = width - mover.radius;
    mover.velocity.x *= -1 * mover.energyConservationRate;
  }else if(mover.position.x < mover.radius){
    mover.velocity.x *= -1 * mover.energyConservationRate;
    mover.position.x = mover.radius;
  }

  if(mover.position.y > height - mover.radius){
    mover.velocity.y *= -1 * mover.energyConservationRate;
    mover.position.y = height - mover.radius;
  }
}

bool isContactingEdge(Body& mover, int width, int height){
  return (mover.position.y > (height - mover.radius - 1));
}

Vector2 setMagnitude(Vector2 vec2, float magnitude){
  return Vector2Normalize(vec2) * magnitude; 
}

Vector2 randomNormailzedVector(){
  float angle = randomFloat(0, 360);
  return Vector2{sinf(angle), cosf(angle)};
}

float randomFloat(float min, float max){
  float random = ((float) rand()) / ((float)RAND_MAX);
  float diff = max - min;
  float r = random * diff;
  return min + r;
}
