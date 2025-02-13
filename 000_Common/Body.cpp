
#include "Body.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdint>
#include "Number.h"

Body::Body(Vector2 position, Vector2 velocity, Vector2 acceleration, float mass, Color color):position{position}, velocity{velocity}, acceleration{acceleration}, mass{mass}, color{color}{};
Body::Body(Vector2 position, float mass, Color color):Body(position, Vector2{0,0}, Vector2{0,0}, mass, color){};
  
void Body::ApplyForce(Vector2 force){
  
  acceleration = Vector2Add(acceleration, force / mass);
}

void Body::Update(uint32_t dt){
  velocity += acceleration;
  position += velocity;

  angularAcceleration = acceleration.x /10.f;
  anglularVelocity += angularAcceleration;
  if(anglularVelocity > 0.1){
    anglularVelocity = 0.1;
  }else if(anglularVelocity < -0.1){
    anglularVelocity = -0.1;
  }
  angle += anglularVelocity;

  acceleration *= 0;
}

void Body::Draw(){
  //BeginDrawing();
  angle = atan2f(velocity.y, velocity.x);
  DrawCircle(position.x, position.y, mass * 16, RED);
  //DrawRectangle(position.x, position.y, mass * 16, mass*16, RED);
  //DrawPolyLines(position, 4, mass * 16, (angle * 180) / PI, RED);
  //DrawLine(position.x, position.y, radius * cosf(angle), radius * sinf(angle), BLACK);

  //EndDrawing();
}

Vector2 Body::Attract(Body& body){
  Vector2 force = Vector2Subtract(this->position, body.position);

  float d = Vector2Length(force);
  if(d < 5){
    d = 5;
  }else if(d > 25){
    d = 25;
  }

  float strength = (1.0 * (this->mass * body.mass)) / (d * d);
  return setMagnitude(force, strength);

}
