#include "symbol.h"
#include "strings.h"

using namespace std;

Type Symbol::getType(){
     return this->type;
}
int Symbol::getSymbol(){
     return this->symbol;
}
void Symbol::printSymbol(){
     if(this->getType() == TERM){
          if(this->getSymbol() != END){
          cout << terminalStrings[this->getSymbol()];
          }
     }
     else if(this->getType() == NONTERM){
           cout << tokenStrings[this->getSymbol()];
     }

}