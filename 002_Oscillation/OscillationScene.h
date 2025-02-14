#ifndef OSCILLATION_OSCILLATION_SCENE_H_
#define OSCILLATION_OSCILLATION_SCENE_H_

#include "Body.h"
#include "Scene.h"
#include "raylib.h"
#include <cstdint>
#include <vector>

class Oscillator {
public:
  Oscillator(int winWidth, int winHeight);
  void Update(double dt);
  void Draw();

  int winWidth;
  int winHeight;

private:
  Vector2 angle{};
  Vector2 angularVelocity{};
  Vector2 amplitude{};
};

class Bob: public Body{
public:
  Bob(Vector2 position = Vector2{0,0},  float mass = 10.f, Color color = RED);
};

class Spring {
public:
  Spring(float x, float y, int restLength);
  
  void Draw();
  
  Vector2 Connnect(Bob& bob);
  void ConstrainLength(Vector2& vector, float min, float max);

  float x;
  float y;
private:
  Vector2 anchor{};
  int restLength;
  float k = 0.002;

};

class Pendulum{
public:
  Pendulum(float x, float y, float r);

  void Update(double dt);
  void Draw();

private:
  Vector2 pivot;
  float r;
  float angle = PI / 4;
  float damping = 0.99;
  
  float angularVelocity = 0;
  float angularAcceleration = 0;
  float ballr = 16;

  Vector2 bob;
};

class OscillationScene: public Scene{

public:
  OscillationScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;
  void DrawGUI();

private:
  std::string name = "Oscillators";
  std::vector<Oscillator> oscillators = {};
  
  Pendulum pendulum = Pendulum(winWidth/2, 100, 100);

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = true;

  Vector2 gravity = {0.0f, 0.1f};
  Vector2 wind = {0.1, 0};
  Vector2 clickForce = {2.f, 2.f};
};

#endif
