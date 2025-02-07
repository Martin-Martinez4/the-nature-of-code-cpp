#ifndef RANDOMNESS_NORMAL_DISTRIBUTION_SCENE_H_
#define RANDOMNESS_NORMAL_DISTRIBUTION_SCENE_H_

#include "Scene.h"
#include <cstdint>
#include <map>
#include <string>
class NormalDistributionScene : public Scene{

public:
  NormalDistributionScene(SceneStack& sceneStack,int winWidth, int winHeight, float bottomPadding = 10.0f, float xPadding = 10.f, float mean = 5.0, float stddev = 2.0, int samples = 10000);
  
  virtual void Init() override;
  virtual void Update(uint32_t dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  //virtual const void HandleInput() override;

  float mean;
  float stddev;
  int samples;
  float bottomPadding;
  float xPadding;

private:
  std::string name = "Normal Distribution";
  std::map<long, unsigned> histogram = {};
};

#endif // !RANDOMNESS_NORMAL_DISTRIBUTION_SCENE_H_

