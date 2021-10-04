#include <iostream>
#include <cstdlib>
#include "heart.h"

Heart::Heart(int v) : RedCard(v){
  Card heart;
  heart.SetValue(v);
  heart.SetColor("red");
  heart.SetSuit('H');
}
string Heart::Description() const {
  Card heart;
  heart.Description();
}