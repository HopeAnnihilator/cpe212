//
// card.h -- CPE 212-01, Fall 2010 -- Project02 -- Classes
//
// Add the missing statements to complete the class declaration below
// and SUBMIT this file for grading !!!
//

#include <string>
using namespace std;

#ifndef CARD_H
#define CARD_H

class Card                      // Class modeling Card ADT
{
 private:
  int value;			        // Card value: 2-10 for number cards, 11-14 for JQKA; 0 for unknown
  string color;			        // Card color: "red", "black", or "unknown"
  char suit;			        // Card suit: 'H' for hearts, 'D' for diamonds, 'C' for clubs, 'S' for spades or 'U' for unknown

 public:
  //******** Add Constructor Prototypes Below  *********//
  /* Add your code here */      // Default constructor prototype: creates card with value 0, color unknown, and suit U
    Card();
  /* Add your code here */	    // Parameterized constructor prototype: creates card with value v, color unknown, and suit U
    Card(int v);
	
  //******** Add Transformer Prototypes Below *********//
  /* Add your code here */      // SetValue prototype: Sets card value equal to v
    void SetValue(int v);
	
  /* Add your code here */      // SetColor prototype: Sets color value equal to c
    void SetColor(string c);
	
  /* Add your code here */      // SetSuit prototype:  Sets suit value equal to s
    void SetSuit(char s);
	
	
  //******** Add Observer Prototypes Below *********//
  /* Add your code here */ 	    // GetValue prototype: Returns current value of value
    int GetValue() const;
	
  /* Add your code here */      // GetColor prototype: Returns current value of color
    string GetColor() const;
	
  /* Add your code here */      // GetSuit prototype:  Returns current value of suit
    char GetSuit() const;
	
  /* Add your code here */      // Description prototype: Polymorphic Function!!!
	                            // Outputs card characteristics - value as a string (see sample output from p01input1.txt)
    string Description() const;
};


#endif


