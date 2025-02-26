
#include "Body.h"
#include "raylib.h"

const float PI_OVER_180 = 0.01745329251994329576923690768489;

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
Vector2 randomNormailzedVector();

float randomFloat(float min, float max);

float mapFloatToRange(float value, float fromMin, float fromMax, float toMin, float toMax);


