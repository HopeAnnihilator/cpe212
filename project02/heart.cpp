#include <iostream>
#include <cstdlib>
#include "heart.h"

Heart::Heart(int v) : RedCard(v){
  Card::SetSuit('H');
}
string Heart::Description() const {
  string output = Card::Description();
  output = output + ", Color = " + Card::GetColor();
  output = output + ", Suit = " + Card::GetSuit();
  return output;
}
