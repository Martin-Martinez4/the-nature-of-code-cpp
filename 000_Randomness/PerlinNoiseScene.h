
#ifndef RANDOMNESS_PERLIN_NOISE_SCENE_H_
#define RANDOMNESS_PERLIN_NOISE_SCENE_H_

#include "Scene.h"
#include "raylib.h"
#include <memory>
class PerlinNoiseScene : public Scene{

public:
  PerlinNoiseScene(SceneStack& sceneStack, int winWidth, int winHeight, float bottomPadding = 10.0f, float xPadding = 10.f, float factor = .5);
  
  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  //virtual const void HandleInput() override;

  float factor;
  float bottomPadding;
  float xPadding;

private:
  std::string name = "Perlin Noise";
  std::unique_ptr<RenderTexture2D> texture2d;
};

#endif

