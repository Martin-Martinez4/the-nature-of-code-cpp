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
  void Update(uint32_t dt);
  void Draw();

  int winWidth;
  int winHeight;

private:
  Vector2 angle{};
  Vector2 angularVelocity{};
  Vector2 amplitude{};
};

class Bob: public Body{
  Bob(Vector2 position = Vector2{0,0},  float mass = 10.f, Color color = RED);
};

class Spring {
public:
  Spring(float x, float y, int restLength);
  // also called bob
  void Connnect(Bob bob);
  float x;
  float y;
private:
  Vector2 anchor{};
  int restLength;
  float k = 0.2;

};

class OscillationScene: public Scene{

public:
  OscillationScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(uint32_t dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;
  void DrawGUI();

private:
  std::string name = "Oscillators";
  std::vector<Oscillator> oscillators = {};

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = true;

  Vector2 gravity = {0.0f, 0.1f};
  Vector2 wind = {0.1, 0};
  Vector2 clickForce = {2.f, 2.f};
};

#endif
