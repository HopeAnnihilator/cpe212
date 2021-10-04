#include <iostream>
#include <cstdlib>
#include "spade.h"

Spade::Spade(int v) : BlackCard(v) {
  Card spade;
  spade.SetValue(v);
  spade.SetColor("black");
  spade.SetSuit('S');
}
string Spade::Description() const {
  Card spade;
  spade.Description();
}