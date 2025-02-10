#include "Number.h"

void bounceOnEdge(Mover& mover, int width, int height){
  if(mover.position.x > width){
    mover.position.x = width;
    mover.velocity.x *= -1;
  }else if(mover.position.x < 0){
    mover.velocity.x *= -1;
    mover.position.x = 0;
  }

  if(mover.position.y > height - mover.radius){
    mover.velocity.y *= -1;
    mover.position.y = height - mover.radius;
  }
}
