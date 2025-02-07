#include "NormalDistributionScene.h"
#include "raylib.h"
#include <map>
#include <random>
#include <string>


NormalDistributionScene::NormalDistributionScene(SceneStack& sceneStack, int winWidth, int winHeight, float bottomPadding, float xPadding, float mean, float stddev, int samples):Scene(sceneStack, winWidth, winHeight), mean{mean}, stddev{stddev}, samples{samples}, bottomPadding{bottomPadding}, xPadding{xPadding}{
  Init();
};

void NormalDistributionScene::Init() {


  std::random_device rd{};
  std::mt19937 gen{rd()};

  std::normal_distribution d{5.0, 5.0};

  // round to int
  // d = normal_distribution, g is the number generator
  // number is rounded to an int
  auto randomInt = [&d, &gen]{return std::lround(d(gen));};

  // 10000 numbers 
  for(auto n{samples}; n; --n){
    ++histogram[randomInt()];
  }


}
void NormalDistributionScene::Update(uint32_t dt) {

}
void NormalDistributionScene::Draw(){
  
    BeginDrawing();
    ClearBackground(WHITE);

    DrawLine(xPadding, winHeight - bottomPadding - 10, winWidth - xPadding, winHeight - bottomPadding -10, BLACK);

    int barStart = xPadding;

    int numOfBars = histogram.size();
    int barWidth = ((winWidth - 2 * xPadding) - numOfBars * 2) / (numOfBars -1);

    for(const auto [k, v] : histogram){

      DrawRectangle(barStart, winHeight - (v/2) - bottomPadding -10, barWidth, v/2, BLUE);
      DrawText(TextFormat("%d", k), barStart + barWidth/4, winHeight - bottomPadding - 5, 2, BLACK);
      barStart+= barWidth + 2;
    }


    EndDrawing();
}
const std::string& NormalDistributionScene::GetSceneName() const {
 return name; 
}
