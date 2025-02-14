#ifndef COMMON_OPTIONS_SCENE_H_
#define COMMON_OPTIONS_SCENE_H_

#include "Scene.h"
#include <functional>
#include <string>
#include <vector>
class OptionsScene: public Scene{
public:
  OptionsScene(SceneStack& sceneStack, int winWidth, int winHeight, std::vector<std::string> options, std::vector<std::function<void()>> actions);
  
  virtual void Init() override;
  virtual void Update(double dt) override;
  virtual void Draw() override;
  virtual const std::string& GetSceneName() const override;
  virtual const void HandleInput() override;

  std::string name = "Options";

  // options array
  std::vector<std::string>options;

  // function/closure array
  std::vector<std::function<void()>>actions;

protected:

  int optionIndex = 0;
  std::string cursor = ">";


};

#endif


