
#ifndef SCENE_H_
#define SCENE_H_
// draw
// update
// handle input

#include <cstdint>
#include <memory>
#include <stack>
#include <string>
#include "raylib.h"
class Scene;

using SceneStack = std::stack<std::shared_ptr<Scene>>;

class Scene{
public: 
  Scene(SceneStack& sceneStack, int winWidth, int winHeight):sceneStack{sceneStack}, winWidth{winWidth}, winHeight{winHeight}{};
  virtual void Init() = 0;
  virtual void Update(double dt) = 0;
  virtual void Draw() = 0;
  virtual const std::string& GetSceneName() const = 0;
  virtual const void HandleInput(){
    if(IsKeyPressed(KEY_BACKSPACE)){
      sceneStack.pop();
    }
  };

protected:
  int winWidth;
  int winHeight;
  SceneStack& sceneStack;
};


#endif


