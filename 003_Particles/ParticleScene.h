#ifndef PARTICLES_PARTICLE_SCENE_H_
#define PARTICLES_PARTICLE_SCENE_H_



#include "Particle.h"
#include "ParticleEmitter.h"
#include "Scene.h"
class ParticleScene: public Scene{

public:
  ParticleScene(SceneStack& sceneStack, int winWidth, int winHeight);

  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;
  void DrawGUI();

private:
  std::string name = "Particles";
  //std::vector<Particle> particles = {};
  ParticleEmitter pe = ParticleEmitter(Vector2{(float)winWidth/2.f, 0}, 200);
  

  float tempX = 0;
  float tempY = 0;
  float tempMass = 1.0f;

  bool isPaused = false;
  Vector2 gravity = {0.0f, 0.1f};

};

#endif // !PARTICLES_PARTICLE_SCENE_H_

