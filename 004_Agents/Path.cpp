
#include "Path.h"
#include "raylib.h"

Path::Path(Vector2 start, Vector2 end, float radius):start{start}, end{end}, radius{radius}{};

void Path::Draw(){
  DrawLineEx(start, end, radius, GRAY);
}



