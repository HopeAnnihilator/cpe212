#include <iostream>
#include <cstdlib>
#include "spade.h"

Spade::Spade(int v) : BlackCard(v) {
Card::SetSuit('S');
}
string Spade::Description() const {
  string output = Card::Description();
  output = output + ", Color = " + Card::GetColor();
  output = output + ", Suit = " + Card::GetSuit();
  return output;
}