#include <iostream>
#include <cstdlib>
#include "club.h"

Club::Club(int v) : BlackCard(v) {
  Card club;
  club.SetValue(v);
  club.SetColor("black");
  club.SetSuit('C');
}
string Club::Description() const {
  Card club;
  club.Description();
}