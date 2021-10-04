#include <iostream>
#include <cstdlib>
#include "club.h"

Club::Club(int v) : BlackCard(v) {
  Card::SetSuit('C');
}
string Club::Description() const {
  string output = Card::Description();
  output = output + ", Color = " + Card::GetColor();
  output = output + ", Suit = " + Card::GetSuit();
  return output;
}

