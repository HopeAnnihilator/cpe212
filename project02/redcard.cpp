#include <iostream>
#include <cstdlib>
#include "redcard.h"

RedCard::RedCard(int v) : Card(v) {
  Card::SetColor("red");
}
string RedCard::Description() const {
  string output = Card::Description();
  output = output + ", Color = " + Card::GetColor();
  return output;
}