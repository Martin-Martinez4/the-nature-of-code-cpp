#include "Number.h"
#include "raymath.h"

void bounceOnEdge(Mover& mover, int width, int height){
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

bool isContactingEdge(Mover& mover, int width, int height){
  return (mover.position.y > (height - mover.radius - 1));
}

Vector2 setMagnitude(Vector2 vec2, float magnitude){
  return Vector2Normalize(vec2) * magnitude; 
}
