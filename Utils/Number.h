
template <typename T>
T simpleClamp(T value, T min, T max){
  if(value < min){
    return min;
  }else if(value > max){
    return max;
  }

  return value;
}


