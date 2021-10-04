#include <iostream>
#include <cstdlib>
#include "diamond.h"

Diamond::Diamond(int v) : RedCard(v) {
  Card::SetSuit('D');
}
string Diamond::Description() const {
  string output = Card::Description();
  output = output + ", Color = " + Card::GetColor();
  output = output + ", Suit = " + Card::GetSuit();
  return output;
}

