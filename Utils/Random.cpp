
#include "Random.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

float fade(float t){
  // fade function as used by Mr. Perlin
  // 6t^5 - 15t^4 + 10t^3
  //return (6 * powf(t, 3)) - (15 * t ) + 10;
  return t * t * t * (6 * t * t - 15 * t + 10); 
}
int inc(int num, int repeatAfter){
  num++;
  if(repeatAfter > 0){
    return num%repeatAfter;
  }

  return num;

}

Vector2 grad(int ix, int iy){
  const unsigned w = 8 * sizeof(unsigned);
  const unsigned s = w /2;
  unsigned a = ix;
  unsigned b = iy;
  a *= 3284157443;

  b^= a << s | a >> w - s;
  b *= 1911520717;

  a ^= b << s | b >> w -s;
  a *= 2048419325;
  float random = a * (3.14159265 / ~(~0u >> 1)); // between 0 and 2*pi

  return Vector2{sin(random), cos(random)};

  
}

float dotGradient(int ix, int iy, float x, float y){
  Vector2 gradient = grad(ix, iy);

  float dx = x - (float)ix;
  float dy = y - (float)iy;

  return (dx * gradient.x + dy * gradient.y);
}

float lerp(float a, float b, float x){
  // return a +  (b - a) * x;
  return (b-a) * (3.0 - x * 2.0) * x * x + a;
}

// Credit: https://www.youtube.com/watch?v=kCIaHqb60Cw
float perlin(float x, float y, float repeatAfter){

  // Determine grid cell corner coordinates
  int x0 = (int)x;
  int y0 = (int)y;
  int x1 = x0 + 1;
  int y1 = y0 + 1;
  
  // compute interpolation weights
  float sx = x - (float)x0;
  float sy = y - (float)y0;

  // compute and interpolate top two corners
  float n0 = dotGradient(x0, y0, x, y);
  float n1 = dotGradient(x1, y0, x, y);
  float ix0 = lerp(n0, n1, sx);
  
  // compute and interpolate bottom two corners
  n0 = dotGradient(x0, y1, x, y);
  n1 = dotGradient(x1, y1, x, y);
  float ix1 = lerp(n0, n1, sx);

  // interpolate between the two previously interpolated values, now in y
  return lerp(ix0, ix1, sy);

}
