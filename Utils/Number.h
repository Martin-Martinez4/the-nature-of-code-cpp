
#include "Body.h"
#include "raylib.h"
template <typename T>
T simpleClamp(T value, T min, T max){
  if(value < min){
    return min;
  }else if(value > max){
    return max;
  }

  return value;
}

void bounceOnEdge(Body& body, int width, int height);
bool isContactingEdge(Body& body, int width, int height);
Vector2 setMagnitude(Vector2 vec2, float magnitude);

float randomFloat(float min, float max);


