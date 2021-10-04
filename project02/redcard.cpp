#include <iostream>
#include <cstdlib>
#include "redcard.h"

RedCard::RedCard(int v) {
  Card redcard;
  redcard.SetValue(v);
  redcard.SetColor("red");
}
string RedCard::Description() const {
  Card redcard;
  redcard.Description();
}