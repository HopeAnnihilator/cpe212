#include <iostream>
#include <cstdlib>
#include "blackcard.h"

BlackCard::BlackCard(int v) : Card(v) {
  Card::SetColor("black");
}
string BlackCard::Description() const {
  string output = Card::Description();
  output = output + ", Color = " + Card::GetColor();
  return output;
}