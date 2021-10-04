#include <iostream>
#include <cstdlib>
#include "blackcard.h"

BlackCard::BlackCard(int v) {
  Card blackcard;
  blackcard.SetValue(v);
  blackcard.SetColor("black");
  //cout << blackcard.Description();
}
string BlackCard::Description() const{
  cout << "hi";
}