

#include "Liquid.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdint>
#include <utility>
#include "Number.h"

Liquid::Liquid(float x, float y, float w, float h, float c):x{x}, y{y}, w{w}, h{h}, c{c}, rectangle(std::move(Rectangle{x,y,w,h})) {};
void Liquid::ApplyForce(Vector2 force){};
void Liquid::Update(uint32_t dt){};
void Liquid::Draw(){
  DrawRectangle(x, y, w, h, Color{100, 255, 100, 150});
};
bool Liquid::ContainsMover(Body& mover){
  return (mover.position.x > x && mover.position.x < x + w && mover.position.y > y && mover.position.y < y + h);
}
Vector2 Liquid::CalculateDrag(Body& mover){
  float speed = Vector2Length(mover.velocity);
  float dragMagnitude = c * speed * speed;

  Vector2 dragForce = mover.velocity;
  dragForce *= -1;
  return setMagnitude(dragForce, dragMagnitude);

}
