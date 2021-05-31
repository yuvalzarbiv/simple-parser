#include "parser.h"
#include "strings.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>




using namespace std;


void Parser::parse(){
     
     
     stack.push_back(Symbol(END, TERM));
     stack.push_back(Symbol(E, NONTERM));
     auto x = stack.back();
     auto a = nextToken();
     printLM();

     while (!((x.getSymbol() == END) && (x.getType() == TERM))){

          int table_index = table.at(x.getSymbol()).at(a.getSymbol());
          if(x.getSymbol() == a.getSymbol() && x.getType() == a.getType()){
               stack.pop_back();
               accepted.push_back(a);
               printLM();
               a = nextToken();

          }
          else if(x.getType() == TERM && x.getSymbol() != a.getSymbol()){
              
               cout << "syntax error" <<endl;
               break;
          }
          
          else if(table_index == -1){
              
               cout << "syntax error" <<endl;
               break;
          }
          else if (table_index != -1){
              
               stack.pop_back();
               for (int j = 0; j < rules.at(table_index).size(); j++){  
                   if(!(rules.at(table_index).at(j).getSymbol() == EPSILON  && rules.at(table_index).at(j).getType() == TERM)){
                    stack.push_back(rules.at(table_index).at(j));
                   }

               }
               printLM();
          }
         
          x = stack.back();
     }
}

terminal Parser::nextTerminalToken (){
     string word;
     inputFile >> word;
     for(int i =0; i< terminalStrings->length() ; i++){
          if(terminalStrings[i] == word){
               return terminal(i);
          }
     }
}

Symbol Parser::nextToken(){
      
     string word;
     inputFile >> word;
     if (word == ""){
          
          return Symbol(END, TERM);
    }
     if(word == "id"){
        return Symbol(0,TERM);
    }
    if(word == "("){
        return Symbol(3,TERM);
    }
    if(word == ")"){
        return Symbol(4,TERM);
    }
    if(word == "+"){
        return Symbol(1,TERM);
    }
    if(word == "*"){
        return Symbol(2,TERM);
    }
    if(word == "e"){
        return Symbol(6,TERM);
    }
    else{
        return Symbol(5,TERM);
    }
}

void Parser::printLM(){

for(size_t i = 0; i < accepted.size(); ++i){
         accepted[i].printSymbol();
          cout<<" ";
    }
cout<<"| ";

vector<Symbol>stack_reverse = stack;
reverse(stack_reverse.begin(),stack_reverse.end());

for(size_t i = 0; i < stack_reverse.size(); ++i){
         stack_reverse[i].printSymbol();
         cout<<" ";  
    }
    cout<<endl;

}