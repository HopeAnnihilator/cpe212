#include <iostream>
#include <cstdlib>
#include "diamond.h"

Diamond::Diamond(int v) : RedCard(v) {
  Card diamond;
  diamond.SetValue(v);
  diamond.SetColor("red");
  diamond.SetSuit('D');
}
string Diamond::Description() const {
  Card diamond;
  diamond.Description();
}