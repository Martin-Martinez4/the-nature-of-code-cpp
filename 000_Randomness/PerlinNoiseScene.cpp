
#include "PerlinNoiseScene.h"
#include "Scene.h"
#include "Random.h"
#include "raylib.h"
#include <memory>
#include <string>
#include <vector>

PerlinNoiseScene::PerlinNoiseScene(SceneStack& sceneStack, int winWidth, int winHeight, float bottomPadding, float xPadding, float factor):Scene(sceneStack, winWidth, winHeight), bottomPadding{bottomPadding}, xPadding{xPadding}, factor{factor}{
  Init();
};

void PerlinNoiseScene::Init(){

  std::vector<Color> data(winWidth*winHeight, BLACK);

  RenderTexture2D target = LoadRenderTexture(winWidth, winHeight);
  BeginTextureMode(target);
  for(int x = 0; x < winHeight; ++x){
    for(int y = 0; y < winWidth; ++y){
      
      float val = 0;
      float freq = factor;
      float amp = 1;

      for(int i = 0; i < 12; ++i){

        val += perlin(x * freq / winWidth, y * freq / winHeight, 255) ;
        freq *= 2;
        amp /= 2;
      }

      val *= 1.2;

      if(val > 1.0f){
        val = 1.0f;
      }else if(val < -1.0f){
        val = -1.0f;
      }

      unsigned char v = (int)(((val + 1.0f)/2)*255);

      //std::cout << (unsigned char)(int)(((val+1.0f)/2)*255) << "\n";
      
      DrawPixel(x, y, (Color){v, v, v, 255});
      //std::cout << val << "\n"

      //if((x/32+y/32)%2 == 0) DrawPixel(x, y, ORANGE);
      //else DrawPixel(x, y, GOLD);
    }
  }

  EndTextureMode();

  texture2d = std::make_unique<RenderTexture2D>(target);
   
}
void PerlinNoiseScene::Update(double dt){}
void PerlinNoiseScene::Draw(){
  BeginDrawing();
  DrawTexture(texture2d.get()->texture, 0, 0, WHITE);
  DrawPixel(0, 0, RED);
  EndDrawing();

}
const std::string& PerlinNoiseScene::GetSceneName() const {
  return name;
}
//const void PerlinNoiseScene::HandleInput(){}
